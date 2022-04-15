
#ifndef ADD_BRUSH_SIZE_BUTTON_H
#define ADD_BRUSH_SIZE_BUTTON_H


#include "../Buttons/Button.h"
#include "../Slider/Slider.h"

class AddBrushSizeButton : public Button {
public:

    AddBrushSizeButton(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, int _delta, Slider *_slider);

    void OnClicked() override;

protected:
    Slider *slider;
    int delta;
    static constexpr unsigned CharacterSize = 50;

    std::string GetButtonTitle();

};

#endif
