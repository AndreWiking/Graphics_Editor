
#ifndef PLUGIN_TOOL_H
#define PLUGIN_TOOL_H

#include <plugin_std.h>
#include "../../../Settings/GlobalSettings.h"

extern GlobalSettings *Settings;

class PluginTool {
public:
    PluginTool(const PPluginInterface *_PluginInterface) : PluginInterface(_PluginInterface) {}

    const PPluginInterface *PluginInterface;
protected:
};


#endif
