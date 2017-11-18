#ifndef __MAX7219MATRIX_H
#define __MAX7219MATRIX_H

#include <assert.h>
#include <unistd.h>
#include <vector>

#include "MAX7219.h"
#include "PoKeysLib.h"

#define MAX7219_PRESCALER 100
#define MAX7219_FRAMEFORMAT 0

typedef std::vector<MAX7219> deviceArray_t;

class PokeyMAX7219Matrix
{
public:
    PokeyMAX7219Matrix(sPoKeysDevice *pokey, uint8_t deviceCount, uint8_t chipSelect);
    virtual ~PokeyMAX7219Matrix(void);

    uint8_t spi(uint8_t data);
    void refreshDisplay();

private:
protected:
    uint8_t _chipSelect;
    uint8_t _deviceCount;
    sPoKeysDevice *_pokey;
    deviceArray_t _drivers;
};

#endif