#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "plugins/common/simhubdeviceplugin.h"
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

PokeyDevicePluginStateManager::PokeyDevicePluginStateManager(LoggingFunctionCB logger)
    : PluginStateManager(logger)
{
    _numberOfDevices = 0; ///< 0 devices discovered
    _devices = (sPoKeysNetworkDeviceSummary *)calloc(sizeof(sPoKeysNetworkDeviceSummary),
        16); ///< 0 initialise the network device summary
}

//! static getter for singleton instance of our class
PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

PokeyDevicePluginStateManager::~PokeyDevicePluginStateManager(void)
{
    // TODO: enable once shtudown implemented
    if (_pluginThread != NULL) {
        if (_pluginThread->joinable()) {
            ceaseEventing();
            _pluginThread->join();
        }
        _deviceMap.clear();
        delete _pluginThread;
        delete _devices;
    }
}

int PokeyDevicePluginStateManager::deliverValue(GenericTLV *data)
{
    assert(data);
    std::shared_ptr<PokeyDevice> device;

    bool ret = targetFromDeviceTargetList(data->name, device);

    if (ret) {
        if (data->type == ConfigType::CONFIG_BOOL) {
            device->targetValue(data->name, (int)data->value);
        }
    }

    return 0;
}

void PokeyDevicePluginStateManager::enumerateDevices(void)
{
    _numberOfDevices = PK_EnumerateNetworkDevices(_devices, 800);

    assert(_numberOfDevices > 0);

    for (int i = 0; i < _numberOfDevices; i++) {
        std::shared_ptr<PokeyDevice> device = std::make_shared<PokeyDevice>(_devices[i], i);

        _logger(LOG_INFO, "    - #%s %s %s (v%d.%d.%d) - %u.%u.%u.%u ", device->serialNumber().c_str(), device->hardwareTypeString().c_str(), device->deviceData().DeviceName,
            device->firmwareMajorMajorVersion(), device->firmwareMajorVersion(), device->firmwareMinorVersion(), device->ipAddress()[0], device->ipAddress()[1],
            device->ipAddress()[2], device->ipAddress()[3]);

        _deviceMap.emplace(device->serialNumber(), device);
    }
}

bool PokeyDevicePluginStateManager::addTargetToDeviceTargetList(std::string target, std::shared_ptr<PokeyDevice> device)
{
    _deviceMap.emplace(target, device);
    return true;
}

bool PokeyDevicePluginStateManager::targetFromDeviceTargetList(std::string key, std::shared_ptr<PokeyDevice> &ret)
{
    std::map<std::string, std::shared_ptr<PokeyDevice>>::iterator it = _deviceMap.find(key);

    if (it != _deviceMap.end()) {
        ret.reset((*it).second.get());
        return true;
    }

    return false;
}

std::shared_ptr<PokeyDevice> PokeyDevicePluginStateManager::device(std::string serialNumber)
{
    std::shared_ptr<PokeyDevice> retVal;

    if (_deviceMap.count(serialNumber)) {
        retVal = _deviceMap.find(serialNumber)->second;
    }
    
    return retVal;
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

bool PokeyDevicePluginStateManager::deviceConfiguration(libconfig::SettingIterator iter, std::shared_ptr<PokeyDevice> pokeyDevice)
{
    bool retVal = true;
    std::string configSerialNumber = "";
    std::string configName = "";

    try {
        iter->lookupValue("serialNumber", configSerialNumber);

        if (pokeyDevice == NULL) {
            _logger(LOG_ERROR, "    - #%s. No physical device. Skipping....", configSerialNumber.c_str());
            retVal = false;
        }
        else {
            iter->lookupValue("name", configName);

            if (configName != pokeyDevice->name().c_str()) {
                uint32_t retValue = pokeyDevice->name(configName);
                if (retValue == PK_OK) {
                    _logger(LOG_INFO, "      - Device name set (%s)", configName.c_str());
                }
                else {
                    _logger(LOG_INFO, "      - Error setting device name (%s)", configName.c_str());
                }
            }
        }
    }
    catch (const libconfig::SettingNotFoundException &nfex) {
        _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
        retVal = false;
    }

    return retVal;
}

bool PokeyDevicePluginStateManager::devicePinsConfiguration(libconfig::Setting *pins, std::shared_ptr<PokeyDevice> pokeyDevice)
{
    /** pin = 4,
        name = "S_OH_GROUND_CALL",
        type = "DIGITAL_INPUT",
        default = 0
    **/

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
                    int defaultValue = 0;

                    if (addTargetToDeviceTargetList(pinName, pokeyDevice)) {

                        if (iter->exists("default"))
                            iter->lookupValue("default", defaultValue);

                        pokeyDevice->addPin(pinName, pinNumber, pinType, defaultValue);
                        _logger(LOG_INFO, "        - [%d] Added target %s on pin %d", pinIndex, pinName.c_str(), pinNumber);
                    }
                }
                else if (pinType == "DIGITAL_INPUT") {
                    pokeyDevice->addPin(pinName, pinNumber, pinType);
                    _logger(LOG_INFO, "        - [%d] Added source %s on pin %d", pinIndex, pinName.c_str(), pinNumber);
                }
                pinIndex++;
            }
            else {
                _logger(LOG_ERROR, "        - [%d] Invalid pin type %s on pin %d", pinIndex, pinType.c_str(), pinNumber);
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

        std::shared_ptr<PokeyDevice> pokeyDevice = device(serialNumber);

        // check that the configuration has the required config sections
        if (!validateConfig(iter)) {
            continue;
        }

        if (deviceConfiguration(iter, pokeyDevice) == 0) {
            continue;
        }

        devicePinsConfiguration(&iter->lookup("pins"), pokeyDevice);
        pokeyDevice->startPolling();
    }

    if (_numberOfDevices > 0) {
        _logger(LOG_INFO, "  - Discovered %d pokey devices", _numberOfDevices);

        retVal = PREFLIGHT_OK;
    }
    else {
        _logger(LOG_INFO, "   - No Pokey devices discovered");
    }

    return retVal;
}
