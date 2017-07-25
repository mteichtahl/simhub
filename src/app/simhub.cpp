#include <assert.h>
#include <utility>

#include "log/clog.h"
#include "simhub.h"

// TODO: FIX EVERYTHING

std::shared_ptr<SimHubEventController> SimHubEventController::_EventControllerInstance = NULL;

genericTLV *AttributeToCGeneric(std::shared_ptr<Attribute> value)
{
    genericTLV *retVal = (genericTLV *)malloc(sizeof(genericTLV));

    retVal->name = (char *)calloc(value->_name.size() + 1, 1);
    strncpy(retVal->name, value->_name.c_str(), value->_name.size());

    switch(value->_type) {
        case BOOL_ATTRIBUTE:
            retVal->type = CONFIG_BOOL;
            retVal->value.bool_value = value->getValue<bool>();
            break;

        case FLOAT_ATTRIBUTE:
            retVal->type = CONFIG_FLOAT;
            retVal->value.float_value = value->getValue<float>();
            break;

        case INT_ATTRIBUTE:
            retVal->type = CONFIG_INT;
            retVal->value.int_value = value->getValue<int>();
            break;

        case STRING_ATTRIBUTE:
            retVal->type = CONFIG_STRING;
            retVal->value.string_value = (char *)calloc(value->getValue<std::string>().size() + 1, 1);
            strncpy(retVal->value.string_value, value->getValue<std::string>().c_str(), value->getValue<std::string>().size());
            break;

        default:
            assert(false);
            break;
    }

    return retVal;
}

//! marshals the C generic struct instance into an Attribute C++ generic container
std::shared_ptr<Attribute> AttributeFromCGeneric(genericTLV *generic)
{
    std::shared_ptr<Attribute> retVal(new Attribute());

    switch (generic->type) {
    case CONFIG_BOOL:
        retVal->setValue<bool>(generic->value.bool_value);
        retVal->_type = BOOL_ATTRIBUTE;
        break;
    case CONFIG_FLOAT:
        retVal->setValue<float>(generic->value.float_value);
        retVal->_type = FLOAT_ATTRIBUTE;
        break;
    case CONFIG_INT:
        retVal->setValue<int>(generic->value.int_value);
        retVal->_type = INT_ATTRIBUTE;
        break;
    case CONFIG_STRING:
        retVal->setValue<std::string>(generic->value.string_value);
        retVal->_type = STRING_ATTRIBUTE;
        break;
    default:
        assert(false);
        break;
    }

    retVal->_name = generic->name;

    return retVal;
}

//! static singleton accessor
std::shared_ptr<SimHubEventController> SimHubEventController::EventControllerInstance(void)
{
    if (!_EventControllerInstance)
        _EventControllerInstance.reset(new SimHubEventController());

    return SimHubEventController::_EventControllerInstance;
}

SimHubEventController::SimHubEventController()
{
    _prepare3dMethods.plugin_instance = NULL;
    _pokeyMethods.plugin_instance = NULL;

    logger.log(LOG_INFO, "Starting event controller");
}

SimHubEventController::~SimHubEventController(void)
{
    terminate();
}

bool SimHubEventController::deliverPokeyPluginValue(std::shared_ptr<Attribute> value)
{
    assert(_pokeyMethods.simplug_deliver_value);

    genericTLV *c_value = AttributeToCGeneric(value);
    bool retVal = !_pokeyMethods.simplug_deliver_value(_pokeyMethods.plugin_instance, c_value);
    
    if(c_value->type == CONFIG_STRING)
        free(c_value->value.string_value);
    free(c_value->name);
    free(c_value);
    
    return retVal;
}
// these callbacks will be called from the thread of the event
// generator which is assumed to not be the thread of the for
// loop below

void SimHubEventController::prepare3dEventCallback(SPHANDLE eventSource, void *eventData)
{
    genericTLV *data = static_cast<genericTLV *>(eventData);
    assert(data != NULL);

    std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(data);
    // findMapping(data->name);
    _eventQueue.push(attribute);
}

void SimHubEventController::pokeyEventCallback(SPHANDLE eventSource, void *eventData)
{
    genericTLV *data = static_cast<genericTLV *>(eventData);
    assert(data != NULL);
    std::shared_ptr<Attribute> attribute = AttributeFromCGeneric(data);
    //std::cout << "pokey event " << attribute->_name << ": " << attribute->getValueToString() << std::endl;
    _eventQueue.push(attribute);
}

void SimHubEventController::LoggerWrapper(const int category, const char *msg, ...)
{
    // TODO: make logger a class instance member
    char buff[MAX_VA_LENGTH];
    va_list args;
    va_start(args, msg);
    vsprintf(buff, msg, args);
    va_end(args);

    logger.log(category, buff);
}

simplug_vtable SimHubEventController::loadPlugin(std::string dylibName, EnqueueEventHandler eventCallback)
{
    SPHANDLE pluginInstance = NULL;
    simplug_vtable pluginMethods;

    memset(&pluginMethods, sizeof(simplug_vtable), 0);

    // TODO: use correct path
    std::string fullPath("plugins/");
    fullPath += dylibName + LIB_EXT;

    int err = simplug_bootstrap(fullPath.c_str(), &pluginMethods);

    if (err == 0) {
        err = pluginMethods.simplug_init(&pluginInstance, SimHubEventController::LoggerWrapper);

        pluginMethods.plugin_instance = pluginInstance;

        if (pluginMethods.simplug_preflight_complete(pluginInstance) == 0) {
            // proxy the C style lambda call through to the member
            // function above
            pluginMethods.simplug_commence_eventing(pluginInstance, eventCallback, this);
        }
        else {
            assert(false);
        }
    }
    else {
        assert(false);
    }

    return pluginMethods;
}

void SimHubEventController::loadPrepare3dPlugin(void)
{
    auto prepare3dCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->prepare3dEventCallback(eventSource, eventData); };
    _prepare3dMethods = loadPlugin("libprepare3d", prepare3dCallback);
}

void SimHubEventController::loadPokeyPlugin(void)
{
    auto pokeyCallback = [](SPHANDLE eventSource, void *eventData, void *arg) { static_cast<SimHubEventController *>(arg)->pokeyEventCallback(eventSource, eventData); };
    _pokeyMethods = loadPlugin("libpokey", pokeyCallback);
}

//! perform shutdown ceremonies on both plugins - this unloads both plugins
void SimHubEventController::terminate(void)
{
    shutdownPlugin(_prepare3dMethods);
    shutdownPlugin(_pokeyMethods);
}

//! private support method - gracefully closes plugin instance represented by pluginMethods
void SimHubEventController::shutdownPlugin(simplug_vtable &pluginMethods)
{
    if (pluginMethods.plugin_instance) {
        pluginMethods.simplug_cease_eventing(pluginMethods.plugin_instance);
        pluginMethods.simplug_release(pluginMethods.plugin_instance);
        pluginMethods.plugin_instance = NULL;
    }
}

