
#include "ColorSlider.h"

ColorSlider::ColorSlider(Widget *_parent, Vector2I _local_position, size_t _size_cord1, size_t _size_cord2,
                         Slider::Orientation _orientation, ColorSlider::ColorChannel _color_channel, unsigned char start_val,
                         Text *_display_text, Image *_result_color)

        : Slider(_parent, _local_position, _size_cord1, _size_cord2, MinSize, MaxSize, start_val,
                 _orientation,
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::RGB_KNOB),
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::RGB_KNOB_PRESSED),
                 0,
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::RGB_LINE)),

          color_channel(_color_channel), display_text(_display_text), result_color(_result_color) {

    back_rgb = ApplicationPtr->resources_manager->GetTexture(back_texture_id).copyToImage();

    UpdateResultColor();
    UpdateDisplayText();
    UpdateRGB_Back();
}

void ColorSlider::OnValueChanged(double _value, double _normalized_value) {

    Settings->BrushColor[color_channel] = round(_value);

    UpdateResultColor();
    UpdateDisplayText();
    for (int type = R; type < CHANNEL_COUNT; ++type)
        color_sliders[type]->UpdateRGB_Back();
}

void ColorSlider::UpdateResultColor() {
    result_color->SetColor(Settings->BrushColor);
}

void ColorSlider::UpdateDisplayText() {
    display_text->SetString("RGB " + Settings->BrushColor.GetRGB_String() + "\nHEX: "
                            + Settings->BrushColor.GetHEX_String());
}

void ColorSlider::UpdateRGB_Back() {
    Color max_res, min_res;
    GetResColors(max_res, min_res);

    for (size_t y = 0; y <  back_rgb.getSize().y; ++y)
        for (size_t x = 0; x <  back_rgb.getSize().x; ++x){
            Color res = MergeColors(max_res, y, min_res, back_rgb.getSize().y - y - 1);
            back_rgb.setPixel(x, y, Color(res.R, res.G, res.B, back_rgb.getPixel(x, y).a));
        }


    back_rgb_texture.loadFromImage(back_rgb);
    background->SetTexture(back_rgb_texture);
}

void ColorSlider::GetResColors(Color &max_res, Color &min_res) {
    switch (color_channel) {
        case R:
            max_res = Color(UINT8_MAX, Settings->BrushColor.G, Settings->BrushColor.B);
            min_res = Color(0,         Settings->BrushColor.G, Settings->BrushColor.B);
            break;
        case G:
            max_res = Color(Settings->BrushColor.R, UINT8_MAX, Settings->BrushColor.B);
            min_res = Color(Settings->BrushColor.R, 0,         Settings->BrushColor.B);
            break;
        case B:
            max_res = Color(Settings->BrushColor.R, Settings->BrushColor.G, UINT8_MAX);
            min_res = Color(Settings->BrushColor.R, Settings->BrushColor.G, 0);
            break;
        case CHANNEL_COUNT:
            break;
    }
}
