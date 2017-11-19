#ifndef __MAX7219_H
#define __MAX7219_H

#include <assert.h>
#include <unistd.h>

class MAX7219
{
public:
    uint8_t shutdown = 1;
    uint8_t digitDecoder = 0;
    uint8_t digitsCount = 8;
    uint8_t intensity = 15;

    unsigned char *digitsData = new unsigned char[8];
    bool *needsRefresh = new bool[12];

    MAX7219(void);
    virtual ~MAX7219(void);

    uint8_t *createData(int index, uint8_t reg, uint8_t value);
    uint8_t *sendDataToOutput(void);
    bool dataToRefresh(void);
    void setShutdown(uint8_t value);
    void setDigitDecoder(uint8_t value);
    void setDigitsCount(uint8_t value);
    void setIntensity(uint8_t value);
    void setDigit(uint8_t digit, uint8_t value);
};

#endif