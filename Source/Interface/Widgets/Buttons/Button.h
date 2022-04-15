#ifndef BUTTON_H
#define BUTTON_H

#include "../Image.h"
#include "../Text/Text.h"

class Button : public Image{
public:

    Button(Widget* _parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id, Vector2F scale,
           void (*_on_click_function)(Widget *called_widget));

    Button(Widget* _parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id, Vector2F scale);

    Button(Widget* _parent, Vector2I _local_position, size_t _texture_id, size_t _pressed_texture_id);

    Button(Widget *_parent, Vector2I _local_position, size_t _texture_id);

    Button(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id,
           size_t _pressed_texture_id);

    void SetText(Text *_text);

protected:
    size_t pressed_texture_id;

    Text* text = nullptr;
    void (*on_click_function)(Widget *called_widget) = nullptr;

    static constexpr Color NormalColor = {255, 255, 255}, PressedColor = {170, 170, 170}, HoveredColor = {210, 210, 210};

    static constexpr double PressedTextScale = 0.95, NormalTextScale = 1.0;

    void SetNormal() override;

    void SetPressed() override;

    void SetHovered() override;

    virtual void OnClicked() override;


};

#endif




