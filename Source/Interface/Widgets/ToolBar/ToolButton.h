
#ifndef EFFECT_BUTTON_H
#define EFFECT_BUTTON_H


#include "../Buttons/Button.h"
#include "Toolbar.h"

class ToolButton : public Button {
public:

    ToolButton(Widget *_parent, Vector2I _local_position, PluginManager::PluginType _tool_id);

    void OnClicked() override;

protected:
    PluginManager::PluginType tool_id;
    Toolbar::Type type;

    static constexpr size_t StandardWidth = 210;
    static constexpr size_t StandardHeight = 80;

    static constexpr size_t TextSize = 80;
};


#endif
