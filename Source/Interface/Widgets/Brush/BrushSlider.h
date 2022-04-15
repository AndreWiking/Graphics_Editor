
#ifndef BRUSH_SLIDER_H
#define BRUSH_SLIDER_H

#include "../Slider/Slider.h"

class BrushSlider : public Slider {
public:
    BrushSlider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2, Orientation _orientation,
                Text *_display_text);

    void OnValueChanged(double _value, double _normalized_value) override;

    void UpdateDisplayText();

protected:
    Text *display_text;

    static constexpr double MinSize = 1;
    static constexpr double MaxSize = 99;
};


#endif
