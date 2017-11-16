#include <assert.h>
#include <iostream>
#include <map>
#include <memory>
#include <uv.h>
#include <vector>

#include "main.h"
#include "plugins/common/simhubdeviceplugin.h"
#include "plugins/common/utils.h"

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
    _name = "pokey";
    _devices = (sPoKeysNetworkDeviceSummary *)calloc(sizeof(sPoKeysNetworkDeviceSummary), 16); ///< 0 initialise the network device summary
}

//! static getter for singleton instance of our class
PokeyDevicePluginStateManager *PokeyDevicePluginStateManager::StateManagerInstance(void)
{
    return _StateManagerInstance;
}

PokeyDevicePluginStateManager::~PokeyDevicePluginStateManager(void)
{
    free(_devices);
    _StateManagerInstance = NULL;
}

void PokeyDevicePluginStateManager::ceaseEventing(void)
{
    PluginStateManager::ceaseEventing();

    for (auto devPair : _deviceMap) {
        devPair.second->stopPolling();
    }
}

int PokeyDevicePluginStateManager::processPokeyDeviceUpdate(std::shared_ptr<PokeyDevice> device)
{
    return 0;
}

int PokeyDevicePluginStateManager::deliverValue(GenericTLV *data)
{
    assert(data);

    int retVal = 0;

    std::shared_ptr<PokeyDevice> device = targetFromDeviceTargetList(data->name);

    if (device) {
        if (data->type == ConfigType::CONFIG_BOOL) {
            retVal = device->targetValue(data->name, (bool)data->value);
        }
        else if (data->type == ConfigType::CONFIG_INT) {
            retVal = device->targetValue(data->name, (int)data->value);
        }
    }
    else {
        std::cout << "NO DEVICE!" << std::endl;
    }

    return retVal;
}

void PokeyDevicePluginStateManager::commenceEventing(EnqueueEventHandler enqueueCallback, void *arg)
{
    _enqueueCallback = enqueueCallback;
    _callbackArg = arg;

    for (auto devPair : _deviceMap) {
        devPair.second->setCallbackInfo(_enqueueCallback, _callbackArg, this);
    }
}

void PokeyDevicePluginStateManager::enumerateDevices(void)
{
    _numberOfDevices = PK_EnumerateNetworkDevices(_devices, 800);

    for (int i = 0; i < _numberOfDevices; i++) {
        try {
            std::shared_ptr<PokeyDevice> device = std::make_shared<PokeyDevice>(this, _devices[i], i);

            if (device->pokey()) {
                _logger(LOG_INFO, "    - #%s %s %s (v%d.%d.%d) - %u.%u.%u.%u ", device->serialNumber().c_str(), device->hardwareTypeString().c_str(),
                    device->deviceData().DeviceName, device->firmwareMajorMajorVersion(), device->firmwareMajorVersion(), device->firmwareMinorVersion(), device->ipAddress()[0],
                    device->ipAddress()[1], device->ipAddress()[2], device->ipAddress()[3]);
            }

            _deviceMap.emplace(device->serialNumber(), device);
        }
        catch (const std::exception &except) {
            _logger(LOG_ERROR, "couldn't connect to referenced pokey device");
        }
    }
}

bool PokeyDevicePluginStateManager::addTargetToDeviceTargetList(std::string target, std::shared_ptr<PokeyDevice> device)
{
    _deviceMap.emplace(target, device);
    return true;
}

std::shared_ptr<PokeyDevice> PokeyDevicePluginStateManager::targetFromDeviceTargetList(std::string key)
{
    std::map<std::string, std::shared_ptr<PokeyDevice>>::iterator it = _deviceMap.find(key);

    if (it != _deviceMap.end()) {
        return (*it).second;
    }

    return NULL;
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

//#define FAKE_POKEY

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

void PokeyDevicePluginStateManager::loadTransform(std::string pinName, libconfig::Setting *transform)
{
    _logger(LOG_INFO, " - transform %s", pinName.c_str());

    if (transform->exists("On") && transform->exists("Off")) {
        std::string transformResultOn;
        std::string transformResultOff;

        transform->lookupValue("On", transformResultOn);
        transform->lookupValue("Off", transformResultOff);
        _pinValueTransforms.emplace(pinName, std::bind(&PokeyDevicePluginStateManager::transformBoolToString, this, std::placeholders::_1, transformResultOff, transformResultOn));
    }
}

void PokeyDevicePluginStateManager::loadMapTo(std::string pinName, libconfig::Setting *mapTo)
{
    for (libconfig::Setting &entry : *mapTo) {
        std::string name;

        entry.lookupValue("name", name);

        _logger(LOG_INFO, " - transform %s", name.c_str());

        if (entry.exists("transform")) {
            loadTransform(pinName, &entry);
        }
    }
}

std::shared_ptr<PokeyDevice> PokeyDevicePluginStateManager::deviceForPin(std::string pinName)
{
    std::shared_ptr<PokeyDevice> retVal;

    for (auto entry : _deviceMap) {
        if (entry.second->ownsPin(pinName)) {
            retVal = entry.second;
        }
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
        _logger(LOG_INFO, "    [%s]  - Found %i pins", pokeyDevice->name().c_str(), pinCount);

        int pinIndex = 0;

        for (libconfig::SettingIterator iter = pins->begin(); iter != pins->end(); iter++) {
            int pinNumber = 0;
            std::string pinName = "";
            std::string pinType = "";
            std::string description = "";
            std::string units = "";
            std::string mapTo = "";
            bool pinDefault = false;
            int defaultValue = 0;

            try {
                iter->lookupValue("pin", pinNumber);
                iter->lookupValue("name", pinName);
                iter->lookupValue("type", pinType);
                iter->lookupValue("description", description);
                iter->lookupValue("units", units);
                if (iter->exists("transform")) {
                    loadTransform(pinName, &iter->lookup("transform"));
                }
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                _logger(LOG_ERROR, "Config file parse error at %s. Skipping....", nfex.getPath());
            }

            if (pokeyDevice->validatePinCapability(pinNumber, pinType)) {
                if (iter->exists("mapTo")) {
                    iter->lookupValue("mapTo", mapTo);
                    assert(!mapContains(_remappedPins, pinName));

                    std::shared_ptr<PokeyDevice> remapTargetDevice = deviceForPin(mapTo);

                    assert(remapTargetDevice);

                    // NOTE: the fact config entries that mapTo must be defined *after* the
                    //       device to which they refer is an explicit limitation
                    _remappedPins[pinName] = std::make_pair(remapTargetDevice, mapTo);
                }

                if (pinType == "DIGITAL_OUTPUT") {

                    if (addTargetToDeviceTargetList(pinName, pokeyDevice)) {

                        if (iter->exists("default"))
                            iter->lookupValue("default", defaultValue);

                        pokeyDevice->addPin(pinIndex, pinName, pinNumber, pinType, defaultValue, description, false);
                        _logger(LOG_INFO, "        - [%d] Added target %s on pin %d", pinIndex, pinName.c_str(), pinNumber);
                    }
                }
                else if (pinType == "DIGITAL_INPUT") {
                    if (iter->exists("default"))
                        iter->lookupValue("default", defaultValue);

                    bool invert = false;
                    if (iter->exists("invert"))
                        iter->lookupValue("invert", invert);

                    pokeyDevice->addPin(pinIndex, pinName, pinNumber, pinType, defaultValue, description, invert);

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

/**
 *   @brief  Default  find a transform by element name
 *
 *   @return TransformFunction or NULL if not found
 */
TransformFunction PokeyDevicePluginStateManager::transformForPinName(std::string name)
{
    TransformMap::iterator it = _pinValueTransforms.find(name);

    if (it != _pinValueTransforms.end()) {
        return (*it).second;
    }

    return NULL;
}

bool PokeyDevicePluginStateManager::pinRemapped(std::string pinName)
{
    return mapContains(_remappedPins, pinName);
}

std::pair<std::shared_ptr<PokeyDevice>, std::string> PokeyDevicePluginStateManager::remappedPinDetails(std::string pinName)
{
    std::pair<std::shared_ptr<PokeyDevice>, std::string> retVal;

    if (mapContains(_remappedPins, pinName)) {
        retVal = _remappedPins[pinName];
    }

    return retVal;
}

bool PokeyDevicePluginStateManager::devicePWMConfiguration(libconfig::Setting *pwm, std::shared_ptr<PokeyDevice> pokeyDevice)
{
    bool retVal = true;
    int pwmCount = pwm->getLength();

    if (pwmCount > 0) {
        _logger(LOG_INFO, "    [%s]  - Found %i PWM Channels", pokeyDevice->name().c_str(), pwmCount);
        int encoderIndex = 0;

        for (libconfig::SettingIterator iter = pwm->begin(); iter != pwm->end(); iter++) {
        }
    }

    return retVal;
}

bool PokeyDevicePluginStateManager::deviceEncodersConfiguration(libconfig::Setting *encoders, std::shared_ptr<PokeyDevice> pokeyDevice)
{
    /**
    {
        # channel 1 - Fast Encoder 1 - uses pins 1 and 2
        encoder = 1,
        name = "",
        description = "",
        default = 100
      }
    **/

    bool retVal = true;
    int encoderCount = encoders->getLength();

    if (encoderCount > 0) {
        _logger(LOG_INFO, "    [%s]  - Found %i encoders", pokeyDevice->name().c_str(), encoderCount);
        int encoderIndex = 0;

        for (libconfig::SettingIterator iter = encoders->begin(); iter != encoders->end(); iter++) {
            int encoderNumber = 0;
            std::string encoderName = "";
            std::string description = "";
            int encoderDefault = 0;
            int encoderMin = 0;
            int encoderMax = 1000;
            int encoderStep = 1;
            int invertDirection = 0;
            std::string units = "";

            try {
                iter->lookupValue("encoder", encoderNumber);
                iter->lookupValue("name", encoderName);
                iter->lookupValue("default", encoderDefault);
                iter->lookupValue("description", description);
                iter->lookupValue("min", encoderMin);
                iter->lookupValue("max", encoderMax);
                iter->lookupValue("step", encoderStep);
                iter->lookupValue("invertDirection", invertDirection);
                iter->lookupValue("units", units);
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                _logger(LOG_ERROR, "Could not find %s. Skipping....", nfex.what());
                continue;
            }

            if (pokeyDevice->validateEncoder(encoderNumber)) {
                pokeyDevice->addEncoder(encoderNumber, encoderDefault, encoderName, description, encoderMin, encoderMax, encoderStep, invertDirection, units);
                _logger(LOG_INFO, "        - [%s] Added encoder %i (%s)", pokeyDevice->name().c_str(), encoderNumber, encoderName.c_str());
                encoderIndex++;
            }
        }
    }
    else {
        retVal = false;
    }

    return retVal;
}

bool PokeyDevicePluginStateManager::deviceDisplaysConfiguration(libconfig::Setting *displays, std::shared_ptr<PokeyDevice> pokeyDevice)
{
    bool retVal = true;
    int displayCount = displays->getLength();
    int displayIndex = 0;

    if (displayCount > 2) {
        retVal = false;
        _logger(LOG_ERROR, "Invalid number of displays (%i). Maximum 2", displayCount);
    }
    else {
        _logger(LOG_INFO, "    [%s]  - Found %i displays", pokeyDevice->name().c_str(), displayCount);
        for (libconfig::SettingIterator iter = displays->begin(); iter != displays->end(); iter++) {
            std::string name = "None";
            std::string type = "";
            int enabled = 0;

            try {
                iter->lookupValue("name", name);
                iter->lookupValue("type", type);
                iter->lookupValue("enabled", enabled);

                _logger(LOG_INFO, "    [%s]  - %s [%s]", pokeyDevice->name().c_str(), name.c_str(), type.c_str());

                int matrixRows = deviceDisplaysGroupsConfiguration(&iter->lookup("groups"), displayIndex, pokeyDevice, type);
                _logger(LOG_INFO, "    [%s]  - Added %i digits", pokeyDevice->name().c_str(), matrixRows);

                pokeyDevice->configMatrixLED(displayIndex, 8, 8, enabled);
                displayIndex = displayIndex + 1;
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                _logger(LOG_ERROR, "Could not find %s. Skipping....", nfex.what());
                continue;
            }
        }
    }

    return retVal;
}

int PokeyDevicePluginStateManager::deviceDisplaysGroupsConfiguration(libconfig::Setting *displayGroups, int displayId, std::shared_ptr<PokeyDevice> pokeyDevice, std::string type)
{
    int groupCount = displayGroups->getLength();
    int totalDigits = 0;

    if (groupCount == 0 || groupCount > 8) {
        _logger(LOG_ERROR, "Invalid number of display groups (%i). Minimum 1 Maximum 8", groupCount);
    }
    else {
        _logger(LOG_INFO, "    [%s]  - Found %i display groups", pokeyDevice->name().c_str(), groupCount);
        int id = 0;
        for (libconfig::SettingIterator iter = displayGroups->begin(); iter != displayGroups->end(); iter++) {
            std::string name = "None";
            int digits = 0;
            int position = 0;

            try {
                iter->lookupValue("name", name);
                iter->lookupValue("digits", digits);
                iter->lookupValue("position", position);

                _logger(LOG_INFO, "    [%s]    - %s %i digits / position %i", pokeyDevice->name().c_str(), name.c_str(), digits, position);
                pokeyDevice->addMatrixLED(displayId, name, type);

                pokeyDevice->addGroupToMatrixLED(id++, displayId, name, digits, position);
                addTargetToDeviceTargetList(name, pokeyDevice);
                totalDigits += digits;
            }
            catch (const libconfig::SettingNotFoundException &nfex) {
                _logger(LOG_ERROR, "Could not find %s. Skipping....", nfex.what());
                continue;
            }
        }
    }
    return totalDigits;
}

int PokeyDevicePluginStateManager::preflightComplete(void)
{
    int retVal = PREFLIGHT_OK;
    libconfig::Setting *devicesConfiguraiton = NULL;

    _preflightComplete = false;

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

#if defined FAKE_POKEY
        sPoKeysNetworkDeviceSummary dummyData;
        std::shared_ptr<PokeyDevice> dev = std::make_shared<PokeyDevice>(this, dummyData, 0);
        dev->setSerialNumber(serialNumber);
        _deviceMap.emplace(dev->serialNumber(), dev);
        _numberOfDevices++;
#endif
        std::shared_ptr<PokeyDevice> pokeyDevice = device(serialNumber);

        // check that the configuration has the required config sections
        if (!validateConfig(iter)) {
            continue;
        }

        if (deviceConfiguration(iter, pokeyDevice) == 0) {
            continue;
        }

        if (iter->exists("pins"))
            devicePinsConfiguration(&iter->lookup("pins"), pokeyDevice);

        // check if there is an encoder section in the config
        if (iter->exists("encoders"))
            deviceEncodersConfiguration(&iter->lookup("encoders"), pokeyDevice);

        // check if there is an displays section in the config
        if (iter->exists("displays"))
            deviceDisplaysConfiguration(&iter->lookup("displays"), pokeyDevice);

        if (iter->exists("pwm"))
            devicePWMConfiguration(&iter->lookup("displays"), pokeyDevice);

        pokeyDevice->startPolling();
    }

    if (_numberOfDevices > 0) {
        _logger(LOG_INFO, "  - Discovered %d pokey devices", _numberOfDevices);
        retVal = PREFLIGHT_OK;
    }
    else {
        _logger(LOG_INFO, "   - WARNING: No Pokey devices discovered");
    }

    _preflightComplete = (retVal == PREFLIGHT_OK);

    return retVal;
}
