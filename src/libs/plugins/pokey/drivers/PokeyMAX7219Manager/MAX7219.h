#ifndef __MAX7219_H
#define __MAX7219_H

#include <vector>
#include <assert.h>
#include <unistd.h>

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

class MAX7219
{
protected:
    std::vector<std::vector<bool>> _stateMatrix;

public:
    MAX7219(void);
    virtual ~MAX7219(void);

    uint16_t encodeOutputPacket(uint8_t reg, uint8_t value);
};

#endif