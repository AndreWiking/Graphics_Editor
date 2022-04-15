
#ifndef TOOL_WIDGET_H
#define TOOL_WIDGET_H


#include "../Widget.h"
#include "ToolButton.h"

class ToolWidget : public Widget {
public:

    ToolWidget(Widget *_parent, Vector2I _local_position, PluginManager::PluginType _tool_id);

    static constexpr size_t StandardWidth = 300;
    static constexpr size_t StandardHeight = 100;
protected:
    PluginManager::PluginType tool_id;

    static constexpr Vector2I LogoPos = {0, 0};
    static constexpr size_t LogoWidth = 80;
    static constexpr size_t LogoHeight = 80;

    static constexpr Vector2I ButtonPos = {100, 0};
};


#endif
