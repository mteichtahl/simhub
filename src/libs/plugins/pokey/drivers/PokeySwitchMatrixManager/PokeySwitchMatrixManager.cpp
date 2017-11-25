
#include "PokeySwitchMatrixManager.h"

PokeySwitchMatrixManager::PokeySwitchMatrixManager(sPoKeysDevice *pokey)
{
    _pokey = pokey;
}

PokeySwitchMatrixManager::~PokeySwitchMatrixManager(void) {}

int PokeySwitchMatrixManager::addMatrix(int id, std::string name, std::string type, bool enabled)
{
    _switchMatrix.push_back(std::make_shared<PokeySwitchMatrix>(_pokey, id, name, type, enabled));
    return 0;
}

std::shared_ptr<PokeySwitchMatrix> PokeySwitchMatrixManager::matrix(std::string name)
{

    for (auto &matrix : _switchMatrix) {
        if (matrix->name() == name) {
            return matrix;
        }
    }

    return NULL;
}

std::shared_ptr<PokeySwitchMatrix> PokeySwitchMatrixManager::matrix(int id)
{

    for (auto &matrix : _switchMatrix) {
        if (matrix->id() == id) {
            return matrix;
        }
    }

    return NULL;
}

std::vector<std::pair<std::string, uint8_t>> PokeySwitchMatrixManager::readAll()
{

    std::vector<std::pair<std::string, uint8_t>> retVal;

    for (auto &matrix : _switchMatrix) {    
        std::vector<std::pair<std::string, uint8_t>> switches = matrix->readSwitches();

        if (switches.size() > 0) {
            retVal.insert(retVal.end(), switches.begin(), switches.end());
        }
    }

    return retVal;
}
