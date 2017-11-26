#ifndef __POKEY_SWITCH_MATRIX_MANAGER_H
#define __POKEY_SWITCH_MATRIX_MANAGER_H

#include "PoKeysLib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "PokeySwitchMatrix.h"


class PokeySwitchMatrixManager
{
protected:
    std::vector<std::shared_ptr<PokeySwitchMatrix>> _switchMatrix;
    sPoKeysDevice *_pokey;

public:
    PokeySwitchMatrixManager(sPoKeysDevice *pokey);
    virtual ~PokeySwitchMatrixManager(void);

    int addMatrix(int id, std::string name, std::string type, bool enabled);
    std::shared_ptr<PokeySwitchMatrix> matrix(std::string name);
    std::shared_ptr<PokeySwitchMatrix> matrix(int id);
    std::vector<GenericTLV *> readAll();
};

#endif
