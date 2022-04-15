
#include "AddBrushSizeButton.h"

AddBrushSizeButton::AddBrushSizeButton(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, int _delta,
                                       Slider *_slider) :
        Button(_parent, _local_position, _width, _height, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_DARK),
               ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_DARK)), delta(_delta), slider(_slider) {

    Text *text = new Text(this, {}, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_DISPLAY),
                          GetButtonTitle(), GlobalSettings::BlackButtonTextColor , CharacterSize);

    this->SetText(text);
}

void AddBrushSizeButton::OnClicked() {
    slider->SetValue(slider->GetValue() + delta);
}

std::string AddBrushSizeButton::GetButtonTitle() {
    std::string res = (delta < 0 ? "-" : "+");
    return res + std::to_string(abs(delta));
}
