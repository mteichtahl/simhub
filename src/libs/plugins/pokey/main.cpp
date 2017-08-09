#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>
#include <uv.h>

#include "common/simhubdeviceplugin.h"
#include "main.h"

// -- public C FFI

extern "C" {

int simplug_init(SPHANDLE *plugin_instance, LoggingFunctionCB logger)
{
    *plugin_instance = new PokeyDevicePluginStateManager(logger);
    return 0;
}

int simplug_config_passthrough(SPHANDLE plugin_instance, void *libconfig_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->configPassthrough(static_cast<libconfig::Config *>(libconfig_instance));
}

int simplug_preflight_complete(SPHANDLE plugin_instance)
{
    return static_cast<PluginStateManager *>(plugin_instance)->preflightComplete();
}

void simplug_commence_eventing(SPHANDLE plugin_instance, EnqueueEventHandler enqueue_callback, void *arg)
{
    static_cast<PluginStateManager *>(plugin_instance)->commenceEventing(enqueue_callback, arg);
}

int simplug_deliver_value(SPHANDLE plugin_instance, GenericTLV *value)
{
    return static_cast<PluginStateManager *>(plugin_instance)->deliverValue(value);
}

void simplug_cease_eventing(SPHANDLE plugin_instance)
{
    static_cast<PluginStateManager *>(plugin_instance)->ceaseEventing();
}

void simplug_release(SPHANDLE plugin_instance)
{
    assert(plugin_instance);
    delete static_cast<PluginStateManager *>(plugin_instance);
}
}

PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::_StateManagerInstance = NULL;

// -- private C++ pokey plugin implementation

#define DEVICE_READ_INTERVAL 100
#define DEVICE_START_DELAY 100

PokeyDevicePluginStateManager::PokeyDevicePluginStateManager(LoggingFunctionCB logger)
    : PluginStateManager(logger)
{
    _numberOfDevices = 0; ///< 0 devices discovered
    _devices = (sPoKeysNetworkDeviceSummary *)calloc(sizeof(sPoKeysNetworkDeviceSummary), 16); ///< 0 initialise the network device summary
}

//! static getter for singleton instance of our class
PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

PokeyDevicePluginStateManager::~PokeyDevicePluginStateManager(void)
{
    if (_pluginThread != NULL) {
        if (_pluginThread->joinable()) {
            ceaseEventing();
            _pluginThread->join();
        }
        _deviceMap.clear();
    }

    if (_uvPollingThread != NULL) {
        if (_uvPollingThread->joinable()) {
            _uvPollingThread->join();
        }
    }
}

void PokeyDevicePluginStateManager::ceaseEventing(void)
{
    assert(_uvPollingLoop);
    uv_stop(_uvPollingLoop);
}

int PokeyDevicePluginStateManager::deliverValue(GenericTLV *value)
{
    assert(value);
    PokeyDevice *device = NULL;

    bool ret = targetFromDeviceTargetList(value->name, device);

    if (ret) {
        _logger(LOG_INFO, "found %s %s %s", value->name, device->name().c_str(), device->serialNumber().c_str());
    }

    return 0;
}

void PokeyDevicePluginStateManager::enumerateDevices(void)
{
    _numberOfDevices = PK_EnumerateNetworkDevices(_devices, 800);
    // assert(_numberOfDevices > 0);

    for (int i = 0; i < _numberOfDevices; i++) {
        PokeyDevice *device = new PokeyDevice(_devices[i], i);

        _logger(LOG_INFO, "    - #%s %s %s (v%d.%d.%d) - %u.%u.%u.%u ", device->serialNumber().c_str(), device->hardwareTypeString().c_str(), device->deviceData().DeviceName,
            device->firmwareMajorMajorVersion(), device->firmwareMajorVersion(), device->firmwareMinorVersion(), device->ipAddress()[0], device->ipAddress()[1],
            device->ipAddress()[2], device->ipAddress()[3]);

        _deviceMap.emplace(device->serialNumber(), device);

        // TODO: enumerate the pin configuration and store in _pins for device
        //       - perhaps put this logic in member fn in PokeyDevice
    }
}

bool PokeyDevicePluginStateManager::addTargetToDeviceTargetList(std::string target, PokeyDevice *device)
{
    _deviceTargetList.emplace(target, device);
    return true;
}

bool PokeyDevicePluginStateManager::targetFromDeviceTargetList(std::string key, PokeyDevice *&ret)
{
    std::map<std::string, PokeyDevice *>::iterator it = _deviceTargetList.find(key);

    if (it != _deviceTargetList.end()) {
        ret = it->second;
        _logger(LOG_INFO, "Pokey plugin to deliver: %s ---- %s", it->first.c_str(), ret->name().c_str());
        return true;
    }

    return false;
}

PokeyDevice *PokeyDevicePluginStateManager::device(std::string serialNumber)
{
    if (_deviceMap.count(serialNumber)) {
        return _deviceMap.find(serialNumber)->second;
    }
    else {
        return NULL;
    }
}

bool PokeyDevicePluginStateManager::validateConfig(libconfig::SettingIterator iter)
{
    bool retValue = true;
    try {
        iter->lookup("pins");
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
        retValue = false;
    }
    return retValue;
}

bool PokeyDevicePluginStateManager::getDeviceConfiguration(libconfig::SettingIterator iter, PokeyDevice *pokeyDevice)
{
    bool retVal = true;
    std::string configSerialNumber = "";
    std::string configName = "";

    try {
        iter->lookupValue("serialNumber", configSerialNumber);
        pokeyDevice = device(configSerialNumber);

        if (pokeyDevice == NULL) {
            _logger(LOG_ERROR, "    - #%s. No physical device. Skipping....", configSerialNumber.c_str());
            retVal = false;
        }
        else {

            iter->lookupValue("name", configName);

            if (configName != pokeyDevice->name().c_str()) {
                _logger(LOG_INFO, "      - Name mismatch. %s <-> %s", configName.c_str(), pokeyDevice->name().c_str());
            }
        }
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
        retVal = false;
    }

    return retVal;
}

bool PokeyDevicePluginStateManager::getDevicePinsConfiguration(libconfig::Setting *pins, PokeyDevice *pokeyDevice)
{
    /** pin = 4,
        name = "S_OH_GROUND_CALL",
        type = "DIGITAL_INPUT",
        default = 0
    **/
    _logger(LOG_INFO, "------- %s", pokeyDevice->name().c_str());

    bool retVal = true;
    int pinCount = pins->getLength();

    if (pinCount > 0) {
        _logger(LOG_INFO, "      - Found %d pins", pinCount);
        int pinIndex = 0;

        for (libconfig::SettingIterator iter = pins->begin(); iter != pins->end(); iter++) {
            int pinNumber = 0;
            std::string pinName = "";
            std::string pinType = "";
            bool pinDefault = false;

            try {
                iter->lookupValue("pin", pinNumber);
                iter->lookupValue("name", pinName);
                iter->lookupValue("type", pinType);
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
            }

            if (pokeyDevice->validatePinCapability(pinNumber, pinType)) {

                if (pinType == "DIGITAL_OUTPUT") {

                    bool poo = addTargetToDeviceTargetList(pinName, pokeyDevice);
                    if (!poo) {
                        _logger(LOG_INFO, "        - [%d] Failed to add target. Duplicate %s", pinIndex, pinName.c_str());
                    }
                    else {
                        _logger(LOG_INFO, "        - [%d] Added target %s on pin %d", pinIndex, pinName.c_str(), pinNumber);
                        pinIndex++;
                    }
                }
            }
            else {
                continue;
            }
        }
    }
    else {
        retVal = false;
    }

    return retVal;
}

int PokeyDevicePluginStateManager::preflightComplete(void)
{
    int retVal = PREFLIGHT_OK;
    libconfig::Setting *devicesConfiguraiton = NULL;

    enumerateDevices();

    try {
        devicesConfiguraiton = &_config->lookup("configuration");
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
    }

    for (libconfig::SettingIterator iter = devicesConfiguraiton->begin(); iter != devicesConfiguraiton->end(); iter++) {

        std::string serialNumber = "";
        iter->lookupValue("serialNumber", serialNumber);

        PokeyDevice *pokeyDevice = device(serialNumber);

        // check that the configuration has the required config sections
        if (!validateConfig(iter)) {
            continue;
        }

        if (getDeviceConfiguration(iter, pokeyDevice) == 0) {
            continue;
        }

        getDevicePinsConfiguration(&iter->lookup("pins"), pokeyDevice);
    }

    if (_numberOfDevices > 0) {
        _logger(LOG_INFO, "  - Discovered %d pokey devices", _numberOfDevices);
        retVal = PREFLIGHT_OK;
    }
    else {
        _logger(LOG_INFO, "   - No Pokey devices discovered");
    }

    startDeviceLoop();

    return retVal;
}


void PokeyDevicePluginStateManager::DigitalIOTimerCallback(uv_timer_t *timer, int status)
{
    PokeyDevicePluginStateManager *pluginInstance = static_cast<PokeyDevicePluginStateManager*>(timer->data);
    printf("poll devices\n");

    // -- poll all devices for new data

    for (std::pair<std::string, PokeyDevice *> devMapping: pluginInstance->_deviceMap) {
        PokeyDevice *device = devMapping.second;
        sPoKeysDevice *pokey = device->pokey();

        // read in all the digital IO from the pokey
        int ret = PK_DigitalIOGet(pokey);

        if (ret == PK_OK) {
            // iterate over the pins 
            for (int i = 0; i < device->pokey()->info.iPinCount; i++) {
                int devicePin = device->pins()[i].pin - 1;
                if (device->pins()[i].type != DIGITAL_INPUT) {
                    continue;
                }

                if (device->pins()[i].value != device->pokey()->Pins[devicePin].DigitalValueGet) {
                    device->pins()[i].previousValue = device->pins()[i].value;
                    device->pins()[i].value = device->pokey()->Pins[devicePin].DigitalValueGet;
                    // TODO: enqueue any changes we observe
                }
            }
        }
    }
}


int PokeyDevicePluginStateManager::startDeviceLoop(void)
{
    _uvPollingTimer.data = this;
    _uvPollingLoop = uv_loop_new();

    uv_timer_init(_uvPollingLoop, &_uvPollingTimer);

    int ret = uv_timer_start(&_uvPollingTimer, 
                             (uv_timer_cb)&PokeyDevicePluginStateManager::DigitalIOTimerCallback, 
                             DEVICE_START_DELAY, 
                             DEVICE_READ_INTERVAL);

    if (ret == 0) {
        _uvPollingThread.reset(new std::thread([=] {
            uv_run(_uvPollingLoop, UV_RUN_DEFAULT);
        }));
    }

    return 1;
}
