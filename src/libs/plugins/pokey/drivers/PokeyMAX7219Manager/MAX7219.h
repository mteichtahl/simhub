#ifndef __MAX7219_H
#define __MAX7219_H

#include "PoKeysLib.h"
#include <assert.h>
#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
using namespace std::chrono_literals;

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)                                                                                                                                                       \
    (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'), (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),              \
        (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

enum eRefreshRegisters {
    REFRESH_SHUTDOWN = 0,
    REFRESH_DECODER = 1,
    REFRESH_COUNT = 2,
    REFRESH_INTENSITY = 3,
    REFRESH_DIGIT_0 = 4,
    REFRESH_DIGIT_1 = 5,
    REFRESH_DIGIT_2 = 6,
    REFRESH_DIGIT_3 = 7,
    REFRESH_DIGIT_4 = 8,
    REFRESH_DIGIT_5 = 9,
    REFRESH_DIGIT_6 = 10,
    REFRESH_DIGIT_7 = 11
};

enum eRegisters {
    REG_DECODE_MODE = 0x9,
    REG_INTENSITY = 0xA,
    REG_SCAN_LIMIT = 0x0B,
    REG_SHUTDOWN = 0xC,
    REG_DISPLAY_TEST = 0xF,
    REG_COL_1 = 0x1,
    REG_COL_2 = 0x2,
    REG_COL_3 = 0x3,
    REG_COL_4 = 0x4,
    REG_COL_5 = 0x5,
    REG_COL_6 = 0x6,
    REG_COL_7 = 0x7,
    REG_COL_8 = 0x8
};

enum eModeValues {
    MODE_SHUTDOWN_ON = 0x0,
    MODE_SHUTDOWN_OFF = 0x1,
    MODE_DECODE_B_OFF = 0x0,
    MODE_DECODE_B_LEADING = 0x1,
    MODE_DECODE_B_TRAILING = 0xF,
    MODE_DECODE_B_ALL = 0xFF,
    MODE_INTENSITY_LOW = 0x1,
    MODE_INTENSITY_MED = 0x7,
    MODE_INTENSITY_HIGH = 0xF,
    MODE_SCAN_LIMIT_ZER = 0x0,
    MODE_SCAN_LIMIT_ALL = 0x7,
    MODE_DISPLAY_TEST_OFF = 0x0,
    MODE_DISPLAY_TEST_ON = 0x1,
    MODE_ROW_1 = 0x1,
    MODE_ROW_2 = 0x2,
    MODE_ROW_3 = 0x4,
    MODE_ROW_4 = 0x8,
    MODE_ROW_5 = 0x10,
    MODE_ROW_6 = 0x20,
    MODE_ROW_7 = 0x40,
    MODE_ROW_8 = 0x80
};

#define MAX7219_PRESCALER 100
#define MAX7219_FRAMEFORMAT 0

class Led;

class MAX7219
{
protected:
    std::vector<std::vector<bool>> _stateMatrix;
    std::vector<std::shared_ptr<Led>> _leds;
    uint8_t _chipSelect;
    int _id;
    std::string _name;
    std::string _matrixType;
    std::string _description;
    uint8_t _enabled;
    sPoKeysDevice *_pokey;
    uint16_t _encodeOutputPacket(uint8_t reg, uint8_t value);

public:
    MAX7219(sPoKeysDevice *pokey, int id, uint8_t chipSelect, std::string matrixType, uint8_t enabled, std::string name, std::string description);
    virtual ~MAX7219(void);

    void setAllPinStates(bool enabled);
    void setPinState(uint8_t col, uint8_t row, bool enabled);
    uint32_t setIntensity(uint8_t intensity);
    uint32_t SPIWrite(uint16_t packet);
    bool runTest(bool cycleThrough = false);
    void addLed(uint8_t ledIndex, std::string name, std::string description, uint8_t enabled, uint8_t row, uint8_t col);

    int id() { return _id; }
    std::string name() { return _name; }
    std::shared_ptr<Led> findLedByName(std::string name);
};


#define ALWAYS_ON 2
class Led
{
protected:
    int _index;
    std::string _name;
    std::string _description;
    uint8_t _enabled;
    uint8_t _row;
    uint8_t _col;
    std::shared_ptr<MAX7219> _owner;

public:
    Led(std::shared_ptr<MAX7219> owner, int index, std::string name, std::string description, uint8_t enabled, uint8_t row, uint8_t col)
    {
        _owner = owner;
        _index = index;
        _name = name;
        _description = description;
        _enabled = enabled;
        _row = row;
        _col = col;

        setState(false);

        if (_enabled) {
            setState(true);
            std::this_thread::sleep_for(150ms);
            setState(false);
        }

        if (_enabled == ALWAYS_ON){
            setState(true);
        }
    }

    void setState(bool val) { _owner->setPinState(_col, _row, val); }
    bool enabled(void) { return _enabled; }
    std::string name(void) { return _name; }
};

#endif