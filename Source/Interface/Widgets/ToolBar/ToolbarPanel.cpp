
#include "ToolbarPanel.h"

ToolbarPanel::ToolbarPanel(Widget *_parent, Vector2I _local_position)
        : Panel(_parent, _local_position, StandardWidth, GetNormalHeight(), StandardName) {

    Vector2I pos = ToolStartPos;
    for (int i = 0; i < PluginManager::PLUGINS_COUNT; ++i) {
        PluginManager::PluginType id = static_cast<PluginManager::PluginType>(i);
        new ToolWidget(this, pos, id);
        pos += ToolDeltaPos;
    }

}

void ToolbarPanel::OnDelete() {
    Panel::OnDelete();
    ApplicationPtr->logic_manager->isPanelOpen[LogicManager::TOOLBAR] = false;
}

size_t ToolbarPanel::GetNormalHeight() {
    return PluginManager::PLUGINS_COUNT * ToolDeltaPos.Y + StandardHeightBounds;
}
