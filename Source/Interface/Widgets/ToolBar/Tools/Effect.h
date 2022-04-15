
#ifndef EFFECT_H
#define EFFECT_H


#include "PluginTool.h"

class Effect : public PluginTool{
public:
    Effect(const PPluginInterface *_PluginInterface) : PluginTool(_PluginInterface) { }

    void Apply();

protected:
};


#endif //EFFECT_H
