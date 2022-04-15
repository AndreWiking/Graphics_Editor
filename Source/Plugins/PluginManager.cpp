
#include "PluginManager.h"

PluginManager* PluginManager::_self = nullptr;

PluginManager *PluginManager::Instance(ResourcesManager *resources_manager) {
    if (!_self) {
        _self = new PluginManager(resources_manager);
    }
    return _self;
}

bool PluginManager::DeleteInstance() {
    if (_self) {
        delete _self;
        _self = 0;
        return true;
    }
    return false;
}

const PPluginInterface *PluginManager::GetInterface(PluginManager::PluginType type) const {
    return Plugins[type]->GetInterface();
}

size_t PluginManager::GetEffectsCount() const { return effects_count; }

size_t PluginManager::GetToolsCount() const { return tools_count;   }

size_t PluginManager::GetIconTextureId(PluginManager::PluginType type) const {
    return icons_id[type];
}

PluginManager::PluginManager(ResourcesManager *resources_manager) {
    for (int i = 0; i < PLUGINS_COUNT; ++i){
        Plugins[i] = new Plugin(PluginItems[i].lib_path);
        if (Plugins[i]->GetErrorCode() != Plugin::OK)
            Plugins[i] = nullptr;
        else {
            if (Plugins[i]->GetInterface()->general.get_info()->type == PPT_EFFECT)
                ++effects_count;
            else
                ++tools_count;
        }
    }
    LoadIconsTextures(resources_manager);
}

void PluginManager::LoadIconsTextures(ResourcesManager *resources_manager) {
    for (size_t i = 0; i < PLUGINS_COUNT; ++i)
        icons_id[i] = resources_manager->AddTexture(PluginItems[i].icon_path);
}

PluginManager::~PluginManager() {
    for (int i = 0; i < PLUGINS_COUNT; ++i)
        delete Plugins[i];
}

