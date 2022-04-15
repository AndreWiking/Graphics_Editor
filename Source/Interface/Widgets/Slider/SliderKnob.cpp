
#include "SliderKnob.h"

SliderKnob::SliderKnob(Widget *_parent, Widget *_slider, Vector2I _local_position, size_t _texture_id, size_t _texture_pressed_id)
        :
        Button(_parent, _local_position,  _texture_id, _texture_pressed_id), slider(_slider) {
}

void SliderKnob::OnPressBegin(Mouse mouse) {
    is_moving = true;
    move_offset = mouse.position - Vector2I(GetWidth() / 2, GetHeight() / 2);
}

void SliderKnob::OnPressEnd(bool is_inside, Mouse mouse) {
    is_moving = false;
}
