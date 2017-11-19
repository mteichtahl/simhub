#include <string.h>

#include "PokeyMAX7219Matrix.h"

PokeyMAX7219Matrix::PokeyMAX7219Matrix(sPoKeysDevice *pokey, uint8_t deviceCount, uint8_t chipSelect)
{
    _chipSelect = chipSelect;
    _deviceCount = deviceCount;
    _pokey = pokey;

    printf("SIZE %i\n", (int)_drivers.size());

    std::shared_ptr<MAX7219> max = std::make_shared<MAX7219>();
    _drivers.push_back(max);
    
    printf("SIZE %i\n", (int)_drivers.size());

    PK_SPIConfigure(_pokey, MAX7219_PRESCALER, MAX7219_FRAMEFORMAT);
}

PokeyMAX7219Matrix::~PokeyMAX7219Matrix(void) {}

std::shared_ptr<MAX7219> PokeyMAX7219Matrix::driver(uint8_t index)
{
    printf("SIZE %i\n", (int)_drivers.size());
    printf("----> index %i\n", index);

    return _drivers.at(index);
}

uint8_t *PokeyMAX7219Matrix::spi(uint8_t *data, uint8_t dataLength)
{
    uint8_t *retVal = (uint8_t *)calloc(dataLength, 1);
    uint8_t status = 0;

    assert(_pokey);

    int32_t result = PK_SPIWrite(_pokey, data, dataLength, _chipSelect);
    result = PK_SPIRead(_pokey, retVal, dataLength);

    return retVal;
}

void PokeyMAX7219Matrix::refreshDisplay(void)
{
    if (_deviceCount > 8)
        _deviceCount = 8;

    bool refreshRequired = true;

    uint8_t *dataToSend = new uint8_t[_deviceCount * 2];

    while (refreshRequired) {
        refreshRequired = false;

        int index = 0;

        for (auto driver: _drivers) {
            uint8_t *data = driver->sendDataToOutput();
            memcpy(dataToSend + (index * 2), data, sizeof(&data));
            index++;
        }

        uint8_t *result = spi(dataToSend, _deviceCount * 2);
        free(result);
    }
}
