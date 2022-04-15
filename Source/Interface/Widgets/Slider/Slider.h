
#ifndef SLIDER_H
#define SLIDER_H

#include "SliderKnob.h"
#include "../../Controllers/GuiManager.h"

extern GuiManager *Gui_Manager;

class Slider : public Widget {
public:

    enum Orientation{ HORIZONTAL = 0, VERTICAL = 1, ORIENTATION_COUNT };

    Slider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2,
           double _min_val, double _max_val, double _start_val, Orientation _orientation);

    Slider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2,
           double _min_val, double _max_val, double _start_val, Orientation _orientation,
           size_t _knob_texture_id, size_t _knob_pressed_texture_id, size_t _rounded_texture_id, size_t _back_texture_id);


    double GetValue() const { return value; }

    void SetValue(double new_val);

    virtual void OnValueChanged(double _value, double _normalized_value) {}

protected:

    Image* background, *rounded;
    SliderKnob* knob;

    size_t knob_texture_id, knob_pressed_texture_id, rounded_texture_id, back_texture_id;
    double min_val, max_val;
    double value;
    double normalized_value; // from 0 to 1
    Orientation orientation;

    void CreateSlider();

    void Update();

    void SetNormalValue(double new_normal_val);

    void OnGlobalMouseMoved(Mouse global_mouse) override;
};


#endif //SLIDER_H
