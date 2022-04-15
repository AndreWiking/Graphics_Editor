
#include "BrushPanel.h"

BrushPanel::BrushPanel(Widget *_parent, Vector2I _local_position)
        : Panel(_parent, _local_position, PanelWidth, PanelHeight, StandardName) {

    Text *text = new Text(this, TextDisplayPos, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_TEXT),
                          "", GlobalSettings::BlackButtonTextColor, StandardTextSize);

    BrushSlider *slider = new BrushSlider(this, SliderPos, StandardLength, StandardHeight, Slider::HORIZONTAL, text);

    new AddBrushSizeButton(this, AddPlusButtonPos, AddButtonWidth, AddButtonHeight, +1, slider);
    new AddBrushSizeButton(this, AddMinusButtonPos, AddButtonWidth, AddButtonHeight, -1, slider);

}

void BrushPanel::OnDelete() {
    Panel::OnDelete();
    ApplicationPtr->logic_manager->isPanelOpen[LogicManager::BRUSH_SIZE] = false;
}
