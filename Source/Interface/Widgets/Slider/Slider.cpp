
#include "Slider.h"

Slider::Slider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2, double _min_val,
               double _max_val, double _start_val, Slider::Orientation _orientation)
        : Widget(_parent, _local_position, _size_cord1, _size_cord2), min_val(_min_val), max_val(_max_val),
          orientation(_orientation) {

    knob_pressed_texture_id = knob_texture_id = ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::SLIDER_KNOB);

    if (orientation == HORIZONTAL){
        rounded_texture_id = ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::SLIDER_ROUNDED_H);
        back_texture_id = ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::SLIDER_BACK_H);
    }
    else if (orientation == VERTICAL){
        rounded_texture_id = ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::SLIDER_ROUNDED_V);
        back_texture_id = ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::SLIDER_BACK_V);
    }

    Gui_Manager->AddSubscribedWidget(this, GuiManager::ON_MOUSE_MOVED);

    CreateSlider();
    SetValue(_start_val);
}

Slider::Slider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2, double _min_val,
               double _max_val, double _start_val, Slider::Orientation _orientation, size_t _knob_texture_id,
               size_t _knob_pressed_texture_id, size_t _rounded_texture_id, size_t _back_texture_id)
        : Widget(_parent, _local_position, _size_cord1, _size_cord2), min_val(_min_val), max_val(_max_val),
          orientation(_orientation),
          knob_texture_id(_knob_texture_id), knob_pressed_texture_id(_knob_pressed_texture_id),
          rounded_texture_id(_rounded_texture_id), back_texture_id(_back_texture_id) {

    Gui_Manager->AddSubscribedWidget(this, GuiManager::ON_MOUSE_MOVED);

    CreateSlider();
    SetValue(_start_val);
}

void Slider::SetValue(double new_val) {
    SetNormalValue((new_val - min_val) / (max_val - min_val));
}

void Slider::CreateSlider() {
    knob = new SliderKnob(this, this, {}, knob_texture_id, knob_pressed_texture_id);

    if (orientation == HORIZONTAL){

        rounded = new Image(this, {}, width, height,
                            rounded_texture_id);
        rounded->SetLocalPosition(Vector2I(0, (int)height / 2 - rounded->GetHeight() / 2));

        background = new Image(this, {}, width, height , back_texture_id);
        background->SetLocalPosition(Vector2I(0, (int)height / 2 - background->GetHeight() / 2));
    }
    else if (orientation == VERTICAL){

        rounded = new Image(this, {}, width, height,
                            rounded_texture_id);
        rounded->SetLocalPosition(Vector2I((int)width / 2 - rounded->GetWidth() / 2, 0));

        background = new Image(this, {}, width, height, back_texture_id);
        background->SetLocalPosition(Vector2I((int)width / 2 - background->GetWidth() / 2, 0));
    }

}

void Slider::Update() {
    value = (max_val - min_val) * normalized_value + min_val;
    if (orientation == HORIZONTAL) {
        knob->SetLocalPosition(Vector2I(GetWidth() * normalized_value - knob->GetWidth() / 2.0,
                                        (int)GetHeight() / 2 - knob->GetHeight() / 2));
        rounded->SetScale(Vector2F(normalized_value, 1));
    }
    else if (orientation == VERTICAL){
        knob->SetLocalPosition(Vector2I((int)GetWidth() / 2 - knob->GetWidth() / 2,
                                        GetHeight() * normalized_value - knob->GetHeight() / 2.0));
        rounded->SetScale(Vector2F(1, normalized_value));
    }

    OnValueChanged(value, normalized_value);
}

void Slider::OnGlobalMouseMoved(Mouse global_mouse) {
    if (knob->is_moving) {
        if (orientation == HORIZONTAL)
            SetNormalValue((double)(global_mouse.position.X - GetGlobalPosition().X - knob->move_offset.X) / GetWidth());
        else if (orientation == VERTICAL)
            SetNormalValue((double)(global_mouse.position.Y - GetGlobalPosition().Y - knob->move_offset.Y) / GetHeight());
    }
}

void Slider::SetNormalValue(double new_normal_val) {
    normalized_value = new_normal_val < 0 ? 0 : new_normal_val > 1 ? 1 : new_normal_val;
    Update();
}
