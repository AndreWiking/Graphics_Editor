
#include "ColorPickerPanel.h"

ColorPickerPanel::ColorPickerPanel(Widget *_parent, Vector2I _local_position)
        : Panel(_parent, _local_position, StandardWidth, StandardHeight, StandardName) {

    Image *resultColor = new Image(this, ResultColorPos, ResultColorWidth, ResultColorHeight,
                                   ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::ROUNDED_SQUARE));

    Text *textResult = new Text(this, TextResultPos, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_TEXT),
                                "", GlobalSettings::BlackButtonTextColor, StandardTextSize);


    for (int type = ColorSlider::R; type < ColorSlider::CHANNEL_COUNT; ++type)
        color_sliders[type] = new ColorSlider(this, SliderPos[type], SliderWidth, SliderHeight, Slider::VERTICAL,
                                              static_cast<ColorSlider::ColorChannel>(type),
                                              Settings->BrushColor[type], textResult, resultColor);

    for (int typeI = ColorSlider::R; typeI < ColorSlider::CHANNEL_COUNT; ++typeI)
        for (int typeJ = ColorSlider::R; typeJ < ColorSlider::CHANNEL_COUNT; ++typeJ)
            color_sliders[typeI]->color_sliders[typeJ] = color_sliders[typeJ];


}

void ColorPickerPanel::OnDelete() {
    Panel::OnDelete();
    ApplicationPtr->logic_manager->isPanelOpen[LogicManager::COLOR_PICKER] = false;
}
