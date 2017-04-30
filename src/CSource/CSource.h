#ifndef __CSOURCE_H
#define __CSOURCE_H

#include "../log/CLog.h"
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>

class CSourceAttribute {
public:
    string attrType;
};

class CSource {
public:
    CSource();
    ~CSource();
    void addAttribute(std::string name, CSourceAttribute attr);

protected:
    string name;
    std::map<std::string, CSourceAttribute> attributes;
};

#endif
