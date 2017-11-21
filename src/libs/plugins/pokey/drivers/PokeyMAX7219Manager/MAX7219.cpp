#include "MAX7219.h"
#include <assert.h>
#include <unistd.h>

MAX7219::MAX7219(void)
{
}

MAX7219::~MAX7219(void)
{
}

// puts a 4 bit register ID and 8 bit register content value
// into a word structure
uint16_t MAX7219::encodeOutputPacket(uint8_t reg, uint8_t value)
{
    uint16_t retVal = 0;

    // NOTE: the register/data bytes are packed in network byte order (MSB)

    retVal = value << 8; // put register in bottom for bits of byte 0
    retVal |= reg; // value in byte 1
    return retVal;
}
