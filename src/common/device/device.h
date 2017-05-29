#ifndef __DEVICE_H
#define __DEVICE_H

#include "../log/clog.h"
#include <libconfig.h++>
#include <string>

class Device
{
protected:
    std::string _type;
    std::string _id;
    libconfig::Setting *_config;

public:
    Device(std::string type, std::string id, libconfig::Setting *config);
    ~Device();
    void show();
};

#endif
