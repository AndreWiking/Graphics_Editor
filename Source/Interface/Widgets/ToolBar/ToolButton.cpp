
#include "ToolButton.h"

ToolButton::ToolButton(Widget *_parent, Vector2I _local_position, PluginManager::PluginType _tool_id)
        : Button(_parent, _local_position, StandardWidth, StandardHeight,
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_BLUE),
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_BLUE)),
          type(ApplicationPtr->tool_bar->GetPluginToolType(_tool_id)), tool_id(_tool_id) {

    const char * name = (*ApplicationPtr->tool_bar->GetEffect(tool_id)->PluginInterface->general.get_info)()->name;

    Text *text = new Text(this, {}, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_DISPLAY), name,
                          GlobalSettings::BlueButtonTextColor, TextSize);
    text->BestSize(GetWidth());

    this->SetText(text);

}

void ToolButton::OnClicked() {
    if (type == Toolbar::EFFECT) {
        if (ApplicationPtr->tool_bar->GetActiveEffect() == ApplicationPtr->tool_bar->GetEffect(tool_id))
            ApplicationPtr->tool_bar->ResetActiveEffect();
        else
            ApplicationPtr->tool_bar->SetActiveEffect(tool_id);
    }
    else {
        if (ApplicationPtr->tool_bar->GetActiveTool() == ApplicationPtr->tool_bar->GetTool(tool_id))
            ApplicationPtr->tool_bar->ResetActiveTool();
        else
            ApplicationPtr->tool_bar->SetActiveTool(tool_id);
    }
}
