
#include "Toolbar.h"

Toolbar* Toolbar::_self = nullptr;

Toolbar *Toolbar::Instance(PluginManager *plugin_manager) {
    if (!_self) {
        _self = new Toolbar(plugin_manager);
    }
    return _self;
}

bool Toolbar::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}

Tool *Toolbar::GetActiveTool() const { return active_tool;   }

Effect *Toolbar::GetActiveEffect() const { return active_effect; }

Tool *Toolbar::GetTool(PluginManager::PluginType tool_id) const { return static_cast<Tool*>(plugin_tools[tool_id]);     }

Effect *Toolbar::GetEffect(PluginManager::PluginType effect_id) const { return static_cast<Effect*>(plugin_tools[effect_id]); }

void Toolbar::SetActiveTool(PluginManager::PluginType tool_id) {
    active_tool   = static_cast<Tool*>(plugin_tools[tool_id]);
    ResetActiveEffect();
}

void Toolbar::SetActiveEffect(PluginManager::PluginType effect_id) {
    active_effect = static_cast<Effect*>(plugin_tools[effect_id]);
    ResetActiveTool();
}

void Toolbar::ResetActiveTool() {active_tool = nullptr;   }

size_t Toolbar::GetEffectsCount() const { return effects_count; }

size_t Toolbar::GetToolsCount() const { return tools_count;   }

Toolbar::Type Toolbar::GetPluginToolType(PluginManager::PluginType id) const { return plugin_tools_type[id]; }

Toolbar::Toolbar(PluginManager *plugin_manager)
        : effects_count(plugin_manager->GetEffectsCount()), tools_count(plugin_manager->GetToolsCount()){

    for (int i = 0; i < PluginManager::PLUGINS_COUNT; ++i) {
        const PPluginInterface * interface = plugin_manager->GetInterface((PluginManager::PluginType)i);
        if (interface->general.get_info()->type == PPT_EFFECT) {
            plugin_tools[i] = new Effect(interface);
            plugin_tools_type[i] = EFFECT;
        }
        else {
            plugin_tools[i] = new Tool(interface);
            plugin_tools_type[i] = TOOL;
        }
    }
}

Toolbar::~Toolbar() {
    for (int i = 0; i < PluginManager::PLUGINS_COUNT; ++i)
        delete plugin_tools[i];
}
