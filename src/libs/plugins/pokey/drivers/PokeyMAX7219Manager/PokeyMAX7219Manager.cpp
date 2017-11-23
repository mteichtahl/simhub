#include <iostream>
#include <thread>

#include "PokeyMAX7219Manager.h"

using namespace std::chrono_literals;

PokeyMAX7219Manager::PokeyMAX7219Manager(sPoKeysDevice *pokey)
{
    _pokey = pokey;
}

PokeyMAX7219Manager::~PokeyMAX7219Manager(void) {}

int PokeyMAX7219Manager::addMatrix(int id, uint8_t chipSelect, std::string matrixType, uint8_t enabled, std::string name, std::string description)
{
    int retVal = 0;
    std::shared_ptr<MAX7219> max7219 = std::make_shared<MAX7219>(_pokey, id, chipSelect, matrixType, enabled, name, description);
    _max7219.push_back(max7219);
    return retVal;
}
