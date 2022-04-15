
#ifndef COLOR_SLIDER_H
#define COLOR_SLIDER_H

#include "../Slider/Slider.h"

class ColorSlider : public Slider {
public:

    enum ColorChannel {
        R = 0, G = 1, B = 2, CHANNEL_COUNT = 3
    };

    ColorSlider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2, Orientation _orientation,
                ColorChannel _color_channel, unsigned char start_val, Text *_display_text, Image *_result_color);

    void OnValueChanged(double _value, double _normalized_value) override;


    void UpdateResultColor();

    void UpdateDisplayText();

    void UpdateRGB_Back();

    ColorSlider *color_sliders[CHANNEL_COUNT];
protected:
    Text *display_text;
    Image *result_color;

    sf::Image back_rgb;
    sf::Texture back_rgb_texture;

    ColorChannel color_channel;

    static constexpr double MinSize = 0;
    static constexpr double MaxSize = UINT8_MAX;

private:

    void GetResColors(Color &max_res, Color &min_res);
};


#endif
