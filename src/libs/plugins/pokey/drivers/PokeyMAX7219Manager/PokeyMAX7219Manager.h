#ifndef __MAX7219MATRIX_H
#define __MAX7219MATRIX_H

#include <assert.h>
#include <unistd.h>
#include <vector>
#include <thread>

#include "MAX7219.h"
#include "PoKeysLib.h"



typedef std::vector<std::shared_ptr<MAX7219>> DeviceVector;

class PokeyMAX7219Manager
{
protected:
    sPoKeysDevice *_pokey;
    std::vector<std::shared_ptr<MAX7219>> _max7219;

public:
    PokeyMAX7219Manager(sPoKeysDevice *pokey);
    int addMatrix(int id, uint8_t chipSelect, std::string matrixType, uint8_t enabled, std::string name, std::string description);
    int addLedToMatrix(int ledMatrixIndex, uint8_t ledIndex, std::string name, std::string description, uint8_t enabled, uint8_t row, uint8_t col);
    std::shared_ptr<MAX7219> getMax7219(int id);

    void setLedByName(std::string name, bool value);


    virtual ~PokeyMAX7219Manager(void);

    


};

#endif
