
#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "Tools/PluginTool.h"
#include "Tools/Effect.h"
#include "../../../Plugins/PluginManager.h"
#include "Tools/Tool.h"

class Toolbar {
public:
    static Toolbar *Instance(PluginManager *plugin_manager);
    static bool DeleteInstance();

    Tool   *GetActiveTool()   const;
    Effect *GetActiveEffect() const;


    Tool   *GetTool(PluginManager::PluginType tool_id)     const;
    Effect *GetEffect(PluginManager::PluginType effect_id) const;


    void SetActiveTool(PluginManager::PluginType tool_id);
    void SetActiveEffect(PluginManager::PluginType effect_id);

    void ResetActiveTool();
    void ResetActiveEffect() {active_effect = nullptr; }

    size_t GetEffectsCount() const;
    size_t GetToolsCount()   const;

    enum Type{
        EFFECT = 0,
        TOOL = 1
    };

    Type GetPluginToolType(PluginManager::PluginType id) const;

private:
    static Toolbar *_self;

    Toolbar(PluginManager *plugin_manager);

    virtual ~Toolbar();

    size_t effects_count = 0, tools_count = 0;


    Effect *active_effect = nullptr;
    Tool   *active_tool   = nullptr;

    PluginTool *plugin_tools[PluginManager::PLUGINS_COUNT] = {};
    Type plugin_tools_type[PluginManager::PLUGINS_COUNT] = {};
};


#endif //TOOLBAR_H
