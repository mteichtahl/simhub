#ifndef __MAX7219MATRIX_H
#define __MAX7219MATRIX_H

#include <assert.h>
#include <unistd.h>
#include <vector>

#include "MAX7219.h"
#include "PoKeysLib.h"

#define MAX7219_PRESCALER 100
#define MAX7219_FRAMEFORMAT 0

typedef std::vector<std::shared_ptr<MAX7219>> DeviceVector;

class PokeyMAX7219Matrix
{
protected:
    uint8_t _chipSelect;
    uint8_t _deviceCount;
    sPoKeysDevice *_pokey;
    DeviceVector _drivers;

public:
    PokeyMAX7219Matrix(sPoKeysDevice *pokey, uint8_t deviceCount, uint8_t chipSelect);
    virtual ~PokeyMAX7219Matrix(void);

    uint8_t *spi(uint8_t *data, uint8_t dataLength);
    std::shared_ptr<MAX7219> driver(uint8_t index);
    void refreshDisplay(void);
};

#endif