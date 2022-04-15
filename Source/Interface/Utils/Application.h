
#ifndef APPLICATION_H
#define APPLICATION_H


#include "../Widgets/ToolBar/Toolbar.h"
#include "../../Plugins/PluginAPI.h"
#include "../../Plugins/PluginManager.h"
#include "../Controllers/ResourcesManager.h"
#include "../Controllers/LogicManager.h"

class Application {
public:
    ResourcesManager *resources_manager;
    PluginManager *plugin_manager;
    Toolbar *tool_bar;
    LogicManager *logic_manager;

    Application(){
        logic_manager = LogicManager::Instance();
        resources_manager = ResourcesManager::Instance();
        plugin_manager = PluginManager::Instance(resources_manager);
        tool_bar = Toolbar::Instance(plugin_manager);
    }

    ~Application(){
        LogicManager::DeleteInstance();
        ResourcesManager::DeleteInstance();
        PluginManager::DeleteInstance();
        Toolbar::DeleteInstance();
    }
private:

};


#endif //APPLICATION_H
