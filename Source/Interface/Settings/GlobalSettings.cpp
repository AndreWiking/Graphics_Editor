
#include "GlobalSettings.h"

GlobalSettings* GlobalSettings::_self = nullptr;

GlobalSettings *GlobalSettings::Instance() {
    if (!_self) {
        _self = new GlobalSettings();
    }
    return _self;
}

bool GlobalSettings::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}


