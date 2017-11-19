#include "MAX7219.h"
#include <assert.h>
#include <unistd.h>

MAX7219::MAX7219(void)
{
    for (int i = 0; i < 12; i++) {
        this->needsRefresh[i] = true;
    }
}

uint8_t *MAX7219::createData(int index, uint8_t reg, uint8_t value)
{
    this->needsRefresh[index] = false;
    uint8_t *retVal = new uint8_t[2];
    retVal[0] = reg;
    retVal[1] = value;
    return retVal;
}

uint8_t *MAX7219::sendDataToOutput(void)
{
    if (this->needsRefresh[0])
        return this->createData(0, 0x0C, this->shutdown); // Shutdown
    if (this->needsRefresh[1])
        return this->createData(1, 0x09, this->digitDecoder); // Digit decoder
    if (this->needsRefresh[2])
        return this->createData(2, 0x0B, this->digitsCount); // Scan limit
    if (this->needsRefresh[3])
        return this->createData(3, 0x0A, this->intensity); // Intensity

    for (int i = 0; i < 8; i++) {
        if (this->needsRefresh[4 + i])
            return createData(4 + i, (uint8_t)(0x01 + i), this->digitsData[i]); // Digit data
    }

    uint8_t *retVal = new uint8_t[2];
    retVal[0] = 0x00;
    retVal[1] = 0x00;

    return retVal;
}

bool MAX7219::dataToRefresh(void)
{
    bool tmp = false;

    for (int i = 0; i < 12; i++) {
        tmp = tmp || this->needsRefresh[i];
    }

    return tmp;
}

void MAX7219::setShutdown(uint8_t value)
{
    this->needsRefresh[0] = (this->shutdown != value);
    this->shutdown = value;
}

void MAX7219::setDigitDecoder(uint8_t value)
{
    this->needsRefresh[1] = (this->digitDecoder != value);
    this->digitDecoder = value;
}

void MAX7219::setDigitsCount(uint8_t value)
{
    this->needsRefresh[2] = (this->digitsCount != value);
    this->digitsCount = value;
}

void MAX7219::setIntensity(uint8_t value)
{
    this->needsRefresh[3] = (this->intensity != value);
    this->intensity = value;
}

void MAX7219::setDigit(uint8_t digit, uint8_t value)
{
    if (digit >= 8)
        return;

    this->needsRefresh[digit + 4] = (this->digitsData[digit] != value);
    this->digitsData[digit] = value;
}

MAX7219::~MAX7219(void)
{
    delete[] digitsData;
    delete[] needsRefresh;
}
