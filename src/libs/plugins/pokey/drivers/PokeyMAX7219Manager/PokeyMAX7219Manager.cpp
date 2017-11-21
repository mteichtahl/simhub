#include <string.h>
#include <thread> 
#include <iostream>

#include "PokeyMAX7219Manager.h"

using namespace std::chrono_literals;

PokeyMAX7219Manager::PokeyMAX7219Manager(sPoKeysDevice *pokey, uint8_t chipSelect)
{
    _chipSelect = chipSelect;
    _pokey = pokey;
    _driver = std::make_shared<MAX7219>();
    _stateMatrix = {{0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0},
                    {0, 0, 0, 0, 0, 0, 0, 0}};
    
    PK_SPIConfigure(_pokey, MAX7219_PRESCALER, MAX7219_FRAMEFORMAT);

    uint16_t packet = 0;
    packet = driver()->encodeOutputPacket(REG_DECODE_MODE, MODE_DECODE_B_OFF);
    deliverDisplayPacket(packet);
    packet = driver()->encodeOutputPacket(REG_SCAN_LIMIT, MODE_SCAN_LIMIT_ALL);
    deliverDisplayPacket(packet);
    packet = driver()->encodeOutputPacket(REG_SHUTDOWN, MODE_SHUTDOWN_OFF);
    deliverDisplayPacket(packet);
    packet = driver()->encodeOutputPacket(REG_DISPLAY_TEST, MODE_DISPLAY_TEST_OFF);
    deliverDisplayPacket(packet);
    packet = 0;
    deliverDisplayPacket(packet);
    packet = driver()->encodeOutputPacket(REG_INTENSITY, MODE_INTENSITY_LOW);
    deliverDisplayPacket(packet);
}

 PokeyMAX7219Manager::~PokeyMAX7219Manager(void) {}

std::shared_ptr<MAX7219> PokeyMAX7219Manager::driver(void)
{
    return _driver;
}

void PokeyMAX7219Manager::setAllPinStates(bool enabled)
{
    for (uint8_t col = 1; col < 9; col++) {
        for (uint8_t row = 1; row < 9; row++) {
            setPinState(col, row, enabled);
        }
    }
}

void PokeyMAX7219Manager::setPinState(uint8_t col, uint8_t row, bool enabled)
{
    assert(col >= 1 && col <= 8 && row >=1 && row <= 8);

    //prepareUpdate(false);

    // this function allows for eight states per column,
    // so get the row mask value with a shift by row
    // (see MODE_ROW_1 -> MODE_ROW_8)

    _stateMatrix[col - 1][row - 1] = enabled;

    // explicitly set the entire row of values to match stored state

    uint8_t colMask = 0;

    for (uint8_t idx = 0; idx < 8; idx++) {
        
        if (_stateMatrix[col - 1][idx]) {
            colMask |= (1 << idx);
        }
    }

    uint16_t packet = driver()->encodeOutputPacket(REG_COL_1 + col - 1, colMask);

    if (deliverDisplayPacket(packet) != PK_OK) {
        throw std::runtime_error("failed to set MAX7219 pin state");
    }
}

/**
 * send MAX7219 packet to device via SPI interface
 */
uint32_t PokeyMAX7219Manager::deliverDisplayPacket(uint16_t packet)
{
    assert(_pokey);
    return PK_SPIWrite(_pokey, (uint8_t *)&packet, sizeof(packet), _chipSelect);
}

bool PokeyMAX7219Manager::RunTests(sPoKeysDevice *pokey, uint8_t chipSelect)
{
    bool retVal = true;

    try {
        std::shared_ptr<PokeyMAX7219Manager> matrixManager = std::make_shared<PokeyMAX7219Manager>(pokey, chipSelect);
        matrixManager->setAllPinStates(true);

        std::this_thread::sleep_for(200ms);
        matrixManager->setAllPinStates(false);

        std::this_thread::sleep_for(200ms);
        for (uint8_t col = 1; col < 9; col++) {
            for (uint8_t row = 1; row < 9; row++) {
                matrixManager->setPinState(col, row, true);
                std::this_thread::sleep_for(20ms);
            }
        }

        std::this_thread::sleep_for(200ms);
        for (uint8_t col = 1; col < 9; col++) {
            for (uint8_t row = 1; row < 9; row++) {
                matrixManager->setPinState(col, row, false);
                std::this_thread::sleep_for(20ms);
            }
        }
    }
    catch (std::runtime_error &err) {
        std::cout << "ERROR: " << err.what() << std::endl;
        retVal = false;
    }

    /*
    std::shared_ptr<MAX7219> output = matrixManager->driver();

    uint16_t packet = 0;
    packet = output->encodeOutputPacket(REG_DECODE_MODE, MODE_DECODE_B_OFF);
    matrixManager->deliverDisplayPacket(packet);
    packet = output->encodeOutputPacket(REG_SCAN_LIMIT, MODE_SCAN_LIMIT_ALL);
    matrixManager->deliverDisplayPacket(packet);
    packet = output->encodeOutputPacket(REG_SHUTDOWN, MODE_SHUTDOWN_OFF);
    matrixManager->deliverDisplayPacket(packet);
    packet = output->encodeOutputPacket(REG_DISPLAY_TEST, MODE_DISPLAY_TEST_OFF);
    matrixManager->deliverDisplayPacket(packet);
    packet = 0;
    matrixManager->deliverDisplayPacket(packet);
    packet = output->encodeOutputPacket(REG_INTENSITY, MODE_INTENSITY_LOW);
    matrixManager->deliverDisplayPacket(packet);

    // more for show than for go, so to speak...

    for (uint8_t col = REG_COL_1; col <= REG_COL_8; col++) {
        packet = output->encodeOutputPacket(col, 0);
        matrixManager->deliverDisplayPacket(packet);
        std::this_thread::sleep_for(200ms);
    }

    for (uint8_t col = REG_COL_1; col <= REG_COL_8; col++) {
        for (uint8_t row = MODE_ROW_1; row <= MODE_ROW_8; row++) {
            packet = output->encodeOutputPacket(col, row);
            matrixManager->deliverDisplayPacket(packet);
            std::this_thread::sleep_for(10ms);
        }
    }
    */

    return retVal;
}