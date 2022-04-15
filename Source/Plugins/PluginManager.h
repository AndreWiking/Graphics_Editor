
#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include "Plugin.h"
#include "../Interface/Controllers/ResourcesManager.h"


class PluginManager {
public:
    static PluginManager *Instance(ResourcesManager *resources_manager);
    static bool DeleteInstance();

    enum PluginType{
        Negative = 0,
        Rainbow,
        Stamp,
        Chromakey,
        Sharpy,
        PLUGINS_COUNT
    };

    const PPluginInterface *GetInterface(PluginType type) const;

    size_t GetEffectsCount() const;
    size_t GetToolsCount()   const;

    size_t GetIconTextureId(PluginType type) const;

private:
    static PluginManager *_self;

    PluginManager(ResourcesManager *resources_manager);
    virtual ~PluginManager();

    void LoadIconsTextures(ResourcesManager *resources_manager);

    size_t effects_count = 0, tools_count = 0;

    struct PluginItem{
        const char *lib_path;
        const char *icon_path;
    };

    static constexpr PluginItem PluginItems[PLUGINS_COUNT] {
            {"Plugins/P_Negative.dylib",     "Images/Inverse.png"},
            {"Plugins/P_Rainbow.dylib",      "Images/rainbow.png"},
            {"Plugins/P_Stamp.dylib",        "Images/DreamTheater.png"},
            {"Plugins/P_Chromakey.dylib",    "Images/Chromakey.png"},
            {"Plugins/P_Sharpy.dylib",       "Images/Sharpy.png"},
    };

    size_t icons_id[PLUGINS_COUNT] = {};

    Plugin *Plugins[PLUGINS_COUNT] = {};
};



#endif
