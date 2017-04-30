#include "CSource.h"

CSource::CSource()
{
    //
    logger.log(LOG_INFO, "go");
};

CSource::~CSource(){};

void CSource::addAttribute(std::string name, CSourceAttribute attr)
{
    //
    attributes.insert(std::pair<string, CSourceAttribute>(name, attr));

    logger.log(LOG_INFO, "map size: %d", attributes.size());
};
