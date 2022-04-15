
#include "Button.h"

Button::Button(Widget *_parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id, Vector2F scale,
               void (*_on_click_function)(Widget *)) :

        Image(_parent, _local_position, _texture_id, scale), pressed_texture_id(_pressed_texture_id),
        on_click_function(_on_click_function) {}

Button::Button(Widget *_parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id, Vector2F scale) :
        Image(_parent, _local_position, _texture_id, scale), pressed_texture_id(_pressed_texture_id) {}

Button::Button(Widget *_parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id) :
        Image(_parent, _local_position, _texture_id), pressed_texture_id(_pressed_texture_id) {}

Button::Button(Widget *_parent, Vector2I _local_position, size_t _texture_id) :
        Image(_parent, _local_position, _texture_id), pressed_texture_id(_texture_id) {}


Button::Button(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id,
               size_t _pressed_texture_id) :
        Image(_parent, _local_position, _width, _height, _texture_id), pressed_texture_id(_pressed_texture_id) {}

void Button::SetText(Text *_text) {
    _text->SetCentrePos();
    text = _text;
}

void Button::SetNormal() {
    state = Normal;
    sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(texture_id));
    sprite.setColor(NormalColor);

    if (text != nullptr) {
        text->GetTextPtr()->setFillColor(MergeTextColors(NormalColor, text->GetColor()));
        text->GetTextPtr()->setScale(text->NormalScale.X * NormalTextScale,
                                     text->NormalScale.Y * NormalTextScale);
    }
}

void Button::SetPressed() {
    state = Pressed;
    sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(pressed_texture_id));
    sprite.setColor(PressedColor);

    if (text != nullptr) {
        text->GetTextPtr()->setFillColor(MergeTextColors(PressedColor, text->GetColor()));
        text->GetTextPtr()->setScale(text->NormalScale.X * PressedTextScale,
                                     text->NormalScale.Y * PressedTextScale);
    }
}

void Button::SetHovered() {
    state = Hovered;
    sprite.setTexture(ApplicationPtr->resources_manager->GetTexture(texture_id));
    sprite.setColor(HoveredColor);

    if (text != nullptr) {
        text->GetTextPtr()->setFillColor(MergeTextColors(HoveredColor, text->GetColor()));
        text->GetTextPtr()->setScale(text->NormalScale.X * NormalTextScale,
                                     text->NormalScale.Y * NormalTextScale);
    }
}

void Button::OnClicked() {
    if (on_click_function != nullptr) on_click_function(this);
}
