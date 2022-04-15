
#ifndef COLOR_PICKER_PANEL_H
#define COLOR_PICKER_PANEL_H

#include "../Panels/Panel.h"
#include "ColorSlider.h"

class ColorPickerPanel : public Panel {
public:
    ColorPickerPanel(Widget *_parent, Vector2I _local_position);

    void OnDelete() override;

protected:
    ColorSlider *color_sliders[ColorSlider::CHANNEL_COUNT];

    static constexpr char StandardName[] = "Color Picker";
    static constexpr size_t StandardWidth = 400;
    static constexpr size_t StandardHeight = 960;

    static constexpr Vector2I ResultColorPos = {60, 90};
    static constexpr size_t ResultColorWidth = 284;
    static constexpr size_t ResultColorHeight = 125;

    static constexpr Vector2I TextResultPos = {30, 845};
    static constexpr size_t StandardTextSize = 33;

    static constexpr size_t SliderWidth = 44;
    static constexpr size_t SliderHeight = 550;

    static constexpr Vector2I SliderPos[ColorSlider::CHANNEL_COUNT] = {{60, 260}, {180, 260}, {300, 260}};

};

#endif
