#include <string.h>

#include "PokeyMAX7219Matrix.h"

PokeyMAX7219Matrix::PokeyMAX7219Matrix(sPoKeysDevice *pokey, uint8_t deviceCount, uint8_t chipSelect)
{

    _chipSelect = chipSelect;
    _deviceCount = deviceCount;
    _pokey = pokey;

    MAX7219 _drivers[_deviceCount];

    PK_SPIConfigure(_pokey, MAX7219_PRESCALER, MAX7219_FRAMEFORMAT);
}

PokeyMAX7219Matrix::~PokeyMAX7219Matrix() {}

uint8_t PokeyMAX7219Matrix::spi(uint8_t data)
{
    uint8_t *retVal = new uint8_t[sizeof(data)];
    uint8_t status = 0;

    assert(_pokey);

    PK_SPIWrite(_pokey, &data, sizeof(data), _chipSelect);
    PK_SPIRead(_pokey, retVal, sizeof(data));

    return *retVal;
}

void PokeyMAX7219Matrix::refreshDisplay()
{
    if (_deviceCount > 8)
        _deviceCount = 8;

    bool refreshRequired = true;

    uint8_t *dataToSend = new uint8_t[_deviceCount * 2];

    while (refreshRequired) {
        refreshRequired = false;

        int index = 0;

        for (deviceArray_t::iterator driver = _drivers.begin(); driver != _drivers.end(); ++driver) {
            index = std::distance(_drivers.begin(), driver);
            uint8_t *data = driver->sendDataToOutput();
            memcpy(dataToSend+(index*2),data,sizeof(&data));           
        }

        spi(*dataToSend);
    }
}
