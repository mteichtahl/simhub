#ifndef __MAX7219MATRIX_H
#define __MAX7219MATRIX_H

#include <assert.h>
#include <unistd.h>
#include <vector>

#include "MAX7219.h"
#include "PoKeysLib.h"

#define MAX7219_PRESCALER   100
#define MAX7219_FRAMEFORMAT 0

typedef std::vector<std::shared_ptr<MAX7219>> DeviceVector;

class PokeyMAX7219Manager
{
protected:
    uint8_t _chipSelect;
    uint8_t _deviceCount;
    sPoKeysDevice *_pokey;
    std::shared_ptr<MAX7219> _driver;
    //! 8x8 LED value array
    std::vector<std::vector<bool>> _stateMatrix;

public:
    PokeyMAX7219Manager(sPoKeysDevice *pokey, uint8_t chipSelect);
    virtual ~PokeyMAX7219Manager(void);

    void setAllPinStates(bool enabled);
    void setPinState(uint8_t col, uint8_t row, bool enabled);

    std::shared_ptr<MAX7219> driver(void);
    uint32_t deliverDisplayPacket(uint16_t packet);

    static bool RunTests(sPoKeysDevice *pokey, uint8_t chipSelect);
};

#endif
