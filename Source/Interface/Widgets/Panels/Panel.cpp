
#include "Panel.h"

Panel::Panel(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, std::string name) :
        Widget(_parent, _local_position, _width, _height, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::PANEL)) {
    type = PANEL;

    header = new PanelHeader(this, {}, _width, HeaderHeight, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::HEADER));

    close = new Button(header, CloseButtonPos, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::CLOSE_BUTTON),
                       ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::CLOSE_PRESSED_BUTTON), Vector2F(1.0, 1.0),
                       [](Widget *called_widget)
                       {
                           called_widget->GetParent()->GetParent()->SetDelete();
                       });

    title = new Text(header, {}, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_TEXT), name,
                     GlobalSettings::StandardTextColor, GlobalSettings::StandardTextOutlineColor,
                     GlobalSettings::StandardTextOutlineThickness, titleSize);

    title->SetCentrePos();
}

void Panel::OnDelete() {
    if (ApplicationPtr->logic_manager->FocusPanel == this) {
        ApplicationPtr->logic_manager->FocusPanel = nullptr;
    }
}
