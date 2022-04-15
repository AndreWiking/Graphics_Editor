
#include "ToolWidget.h"

ToolWidget::ToolWidget(Widget *_parent, Vector2I _local_position, PluginManager::PluginType _tool_id)
        : Widget(_parent, _local_position, StandardWidth, StandardHeight), tool_id(_tool_id) {

    new Image(this, LogoPos, LogoWidth, LogoHeight, ApplicationPtr->plugin_manager->GetIconTextureId(tool_id));

    new ToolButton(this, ButtonPos, tool_id);
}
