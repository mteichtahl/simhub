#ifndef __INC_POKEYSOURCE_MAIN_H
#define __INC_POKEYSOURCE_MAIN_H

#include <assert.h>
#include <iostream>
#include <iterator>
#include <thread>
#include <unistd.h>

#include "PoKeysLib.h"
#include "common/private/pluginstatemanager.h"
#include "common/simhubdeviceplugin.h"
#include "pokeyDevice.h"

#define PREFLIGHT_OK 0
#define PREFLIGHT_FAIL 1

typedef std::pair<std::string, std::shared_ptr<PokeyDevice>> pokeyDevicePair;
typedef std::map<std::string, std::shared_ptr<PokeyDevice>> PokeyDeviceMap; ///< a list of unique device pointers
typedef PokeyDeviceMap::iterator deviceTargetIterator; ///< iterator for deviceTargers

typedef std::function<std::string(std::string, std::string, std::string)> TransformFunction;
typedef std::map<std::string, TransformFunction> TransformMap;

//! barest specialisation of the internal plugin management support base class
class PokeyDevicePluginStateManager : public PluginStateManager
{
private:
    //! simple implementation of class instance singleton
    static PokeyDevicePluginStateManager *_StateManagerInstance;
    static PokeyDevicePluginStateManager *StateManagerInstance(void);
    PokeyDeviceMap _deviceTargetList;
    bool _preflightComplete;

protected:
    bool validateConfig(libconfig::SettingIterator);
    bool deviceConfiguration(libconfig::SettingIterator iter, std::shared_ptr<PokeyDevice> pokeyDevice);
    bool devicePinsConfiguration(libconfig::Setting *pins, std::shared_ptr<PokeyDevice> pokeyDevice);
    bool deviceEncodersConfiguration(libconfig::Setting *encoders, std::shared_ptr<PokeyDevice> pokeyDevice);
    bool deviceDisplaysConfiguration(libconfig::Setting *displays, std::shared_ptr<PokeyDevice> pokeyDevice);
    bool devicePWMConfiguration(libconfig::Setting *pwm, std::shared_ptr<PokeyDevice> pokeyDevice);
    int deviceDisplaysGroupsConfiguration(libconfig::Setting *displayGroups, int id, std::shared_ptr<PokeyDevice> pokeyDevice, std::string type);
    bool addTargetToDeviceTargetList(std::string, std::shared_ptr<PokeyDevice> device);
    std::shared_ptr<PokeyDevice> targetFromDeviceTargetList(std::string);
    void enumerateDevices(void);
    void loadTransform(std::string pinName, libconfig::Setting *transform);
    void loadMapTo(std::string pinName, libconfig::Setting *mapTo);

    int _numberOfDevices;
    PokeyDeviceMap _deviceMap;
    sPoKeysNetworkDeviceSummary *_devices;
    TransformMap _pinValueTransforms;
    std::map<std::string, std::pair<std::shared_ptr<PokeyDevice>, std::string>> _remappedPins;
    std::mutex _pinRemappingMutex;

    std::pair<std::string, GenericTLV *> _coalescedDeliveryValue;
    std::atomic<bool> _pendingCoalescedDelivery;

public:
    PokeyDevicePluginStateManager(LoggingFunctionCB logger);
    virtual ~PokeyDevicePluginStateManager(void);
    int preflightComplete(void);
    void commenceEventing(EnqueueEventHandler enqueueCallback, void *arg);
    virtual int deliverValue(GenericTLV *value);
    virtual void ceaseEventing(void);
    std::shared_ptr<PokeyDevice> device(std::string);
    virtual int processPokeyDeviceUpdate(std::shared_ptr<PokeyDevice> device);

    //! returns the value transformation for the given pin name
    TransformFunction transformForPinName(std::string name);

    //! allows callers to check if a given pin has a remapping
    bool pinRemapped(std::string pinName);

    //! returns the final target device and ping from the give original source pin
    std::pair<std::shared_ptr<PokeyDevice>, std::string> remappedPinDetails(std::string pinName);

    //! KLUDGE: will refactor
    std::mutex &pinRemappingMutex(void) { return _pinRemappingMutex; };

    std::shared_ptr<PokeyDevice> deviceForPin(std::string pinName);

    bool successfulPreflightCompleted(void) { return _preflightComplete; };

    std::pair<std::string, GenericTLV *> &coalescedDeliveryValue(void) { return _coalescedDeliveryValue; };
    std::atomic<bool> &pendingCoalescedDelivery(void) { return _pendingCoalescedDelivery; };
};

#endif
