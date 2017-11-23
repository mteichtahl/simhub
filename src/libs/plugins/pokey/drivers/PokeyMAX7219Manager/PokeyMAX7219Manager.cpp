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

std::shared_ptr<MAX7219> PokeyMAX7219Manager::getMax7219(int id)
{

    std::shared_ptr<MAX7219> retVal;

    for (auto &max7219 : _max7219) {
        if (max7219->id() == id) {
            retVal = max7219;
            break;
        }
    }

    return retVal;
}

int PokeyMAX7219Manager::addLedToMatrix(int ledMatrixIndex, uint8_t ledIndex, std::string name, std::string description, uint8_t enabled, uint8_t row, uint8_t col)
{

    if (enabled) {
        std::shared_ptr<MAX7219> max7219 = getMax7219(ledMatrixIndex);
        assert(max7219);
        max7219->addLed(ledIndex, name, description, enabled, row, col);
    }

    return 0;
}
