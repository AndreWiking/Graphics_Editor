
#include "LogicManager.h"

LogicManager* LogicManager::_self = nullptr;

LogicManager *LogicManager::Instance() {
    if (!_self) {
        _self = new LogicManager();
    }
    return _self;
}

bool LogicManager::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}
