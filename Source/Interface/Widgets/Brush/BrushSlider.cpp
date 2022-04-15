
#include "BrushSlider.h"

BrushSlider::BrushSlider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2,
                         Slider::Orientation _orientation, Text *_display_text)
        : Slider(_parent, _local_position, _size_cord1, _size_cord2, MinSize, MaxSize, Settings->BrushSize, _orientation),
          display_text(_display_text) {

    UpdateDisplayText();
}

void BrushSlider::OnValueChanged(double _value, double _normalized_value) {
    Settings->BrushSize = value;
    UpdateDisplayText();
}

void BrushSlider::UpdateDisplayText() {

    display_text->SetString(std::to_string((int)round(value)));
}
