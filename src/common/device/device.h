#ifndef __DEVICE_H
#define __DEVICE_H

#include "../log/clog.h"
#include <libconfig.h++>
#include <string>
#include <memory>

class Device
{
protected:
    std::string _type;
    std::string _id;
    libconfig::Setting *_config; //< reference to setting owned by other class instance

public:
    Device(std::string type, std::string id, libconfig::Setting *config);
    ~Device(void);
    void show();
};

#endif
