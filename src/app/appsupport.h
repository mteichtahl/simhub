#ifndef __INC_APPSUPPORT_H
#define __INC_APPSUPPORT_H

template <typename T, typename E> bool mapContains(const std::map<T, E> &mapInstance, T key)
{
    return mapInstance.find(key) != mapInstance.end();
}

#endif
