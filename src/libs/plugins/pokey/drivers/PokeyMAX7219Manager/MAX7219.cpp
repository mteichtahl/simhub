#include "MAX7219.h"
#include <assert.h>
#include <string>
#include <unistd.h>
using namespace std::chrono_literals;

MAX7219::MAX7219(sPoKeysDevice *pokey, int id, uint8_t chipSelect, std::string matrixType, uint8_t enabled, std::string name, std::string description)
{
    _chipSelect = chipSelect;
    _id = id;
    _matrixType = matrixType;
    _description = description;
    _pokey = pokey;

    _stateMatrix = { { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0 } };

    PK_SPIConfigure(_pokey, MAX7219_PRESCALER, MAX7219_FRAMEFORMAT);
    uint16_t packet = 0;
    packet = _encodeOutputPacket(REG_DECODE_MODE, MODE_DECODE_B_OFF);
    SPIWrite(packet);
    packet = _encodeOutputPacket(REG_SCAN_LIMIT, MODE_SCAN_LIMIT_ALL);
    SPIWrite(packet);
    packet = _encodeOutputPacket(REG_SHUTDOWN, MODE_SHUTDOWN_OFF);
    SPIWrite(packet);
    packet = _encodeOutputPacket(REG_DISPLAY_TEST, MODE_DISPLAY_TEST_OFF);
    SPIWrite(packet);

    setIntensity(MODE_INTENSITY_MED);

    assert(runTest());
}

MAX7219::~MAX7219(void) {}

// puts a 4 bit register ID and 8 bit register content value
// into a word structure
uint16_t MAX7219::_encodeOutputPacket(uint8_t reg, uint8_t value)
{
    uint16_t retVal = 0;

    // NOTE: the register/data bytes are packed in network byte order (MSB)

    retVal = value << 8; // put register in bottom for bits of byte 0
    retVal |= reg; // value in byte 1
    return retVal;
}

uint32_t MAX7219::SPIWrite(uint16_t packet)
{
    assert(_pokey);
    return PK_SPIWrite(_pokey, (uint8_t *)&packet, sizeof(packet), _chipSelect);
}

uint32_t MAX7219::setIntensity(uint8_t intensity)
{
    uint16_t packet = 0;
    packet = _encodeOutputPacket(REG_INTENSITY, intensity);
    return SPIWrite(packet);
}

void MAX7219::setAllPinStates(bool enabled)
{
    for (uint8_t col = 1; col < 9; col++) {
        for (uint8_t row = 1; row < 9; row++) {
            setPinState(col, row, enabled);
        }
    }
}

void MAX7219::setPinState(uint8_t col, uint8_t row, bool enabled)
{
    assert(col >= 1 && col <= 8 && row >= 1 && row <= 8);
    _stateMatrix[col - 1][row - 1] = enabled;
    uint8_t rowMask = 0;
    uint8_t colRegister = REG_COL_1 + col - 1;

    for (uint8_t idx = 0; idx < 8; idx++) {
        if (_stateMatrix[col - 1][idx]) {
            rowMask |= (1 << idx);
        }
    }

    uint16_t packet = _encodeOutputPacket(colRegister, rowMask);

    if (SPIWrite(packet) != PK_OK) {
        throw std::runtime_error("failed to set MAX7219 pin state");
    }
}

bool MAX7219::runTest(bool cycleThrough)
{
    bool retVal = true;

    try {
        setAllPinStates(true);
        std::this_thread::sleep_for(500ms);
        setAllPinStates(false);
        std::this_thread::sleep_for(250ms);

        if (cycleThrough) {
            for (uint8_t col = 1; col < 9; col++) {
                for (uint8_t row = 1; row < 9; row++) {
                    setPinState(col, row, true);
                    std::this_thread::sleep_for(80ms);
                }
            }
        }

        setAllPinStates(false);
    }
    catch (std::runtime_error &err) {
        std::cout << "ERROR: " << err.what() << std::endl;
        retVal = false;
    }

    return retVal;
}

void MAX7219::addLed(uint8_t ledIndex, std::string name, std::string description, uint8_t enabled, uint8_t row, uint8_t col)
{
    if (enabled) {
        std::shared_ptr<Led> led = std::make_shared<Led>(this, ledIndex, name, description, enabled, row, col);
        _leds.push_back(led);
    }
}
