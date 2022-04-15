
#ifndef SLIDER_KNOB_H
#define SLIDER_KNOB_H

#include "../Widget.h"
#include "../Buttons/Button.h"

class SliderKnob : public Button {
public:

    SliderKnob(Widget *_parent, Widget *_slider, Vector2I _local_position, size_t _texture_id, size_t _texture_pressed_id);

    void OnPressBegin(Mouse mouse) override;

    void OnPressEnd(bool is_inside, Mouse mouse) override;

    bool is_moving = false;
    Vector2I move_offset;
protected:
    Widget *slider;
};

#endif
