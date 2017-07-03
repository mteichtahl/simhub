#include "device.h"

Device::Device(std::string type, std::string id, std::unique_ptr<libconfig::Setting> config)
    : _type(type)
    , _id(id)
    , _config(std::move(config))
{
    logger.log(LOG_INFO, " - Creating %s device #%s with %d elements", _type.c_str(), _id.c_str(), _config->getLength());
}

Device::~Device()
{
}

void Device::show()
{
    logger.log(LOG_INFO, "[%s] %s", _id.c_str(), _type.c_str());
}
