#ifndef APP_H
#define APP_H

#include "Canvas.h"
#include "../Interface/Controllers/GuiManager.h"
#include "../Interface/Widgets/Buttons/Button.h"
#include "../Interface/Widgets/Text/Text.h"
#include "../Interface/Widgets/Panels/Panel.h"
#include "../Interface/Widgets/Paint/PaintCanvas.h"
#include "../Interface/Widgets/Slider/Slider.h"
#include "../Interface/Widgets/Brush/BrushSlider.h"
#include "../Interface/Widgets/Brush/BrushPanel.h"
#include "../Interface/Widgets/ColorPicker/ColorPickerPanel.h"
#include "../Interface/Widgets/Buttons/OpenPanelButton.h"

class App {
public:

    App(const char *window_name, size_t width, size_t height, unsigned fps_limit);

    ~App(){}

    void Run();

    void CreateInterface();

    enum ErrorCode{
    };

private:
    Canvas canvas;

    static const Color TextColor;

    void WorkEvents();

    static constexpr Vector2I OpenButtonsStartPos = {50, 100};
    static constexpr Vector2I OpenButtonsDeltaPos = {0, 200};
    static constexpr size_t OpenButtonsWidth = 300, OpenButtonsHeight = 150;

    void CreateOpenButtons(Widget *root);

    void LoadStandardResources();

    const ResourcesManager::ResourceItem<ResourcesManager::StandardTextures> standard_texture_items[ResourcesManager::STANDARD_TEXTURES_COUNT]
            {
                    {ResourcesManager::BACKGROUND,              "Images/background.jpg"},
                    {ResourcesManager::HEADER,                  "Images/Header.png"},
                    {ResourcesManager::PANEL,                   "Images/PanelBack.png"},
                    {ResourcesManager::CLOSE_BUTTON,            "Images/Close.png"},
                    {ResourcesManager::CLOSE_PRESSED_BUTTON,    "Images/Close_PR.png"},
                    {ResourcesManager::SLIDER_KNOB,             "Images/SliderKnob.png"},
                    {ResourcesManager::SLIDER_BACK_H,           "Images/SliderBack_H.png"},
                    {ResourcesManager::SLIDER_ROUNDED_H,        "Images/SliderRounded_H.png"},
                    {ResourcesManager::SLIDER_BACK_V,           "Images/SliderBack_V.png"},
                    {ResourcesManager::SLIDER_ROUNDED_V,        "Images/SliderRounded_V.png"},
                    {ResourcesManager::BUTTON_DARK,             "Images/Button.png"},
                    {ResourcesManager::BUTTON_WHITE,            "Images/ButtonWhite.png"},
                    {ResourcesManager::BUTTON_BLUE,             "Images/ButtonBlue.png"},
                    {ResourcesManager::RGB_KNOB,                "Images/RGB_Knob.png"},
                    {ResourcesManager::RGB_KNOB_PRESSED,        "Images/RGB_Knob_PR.png"},
                    {ResourcesManager::RGB_LINE,                "Images/RGB_Line.png"},
                    {ResourcesManager::RGB_ROUNDED_LINE,        "Images/RGB_Rounded_Line.png"},
                    {ResourcesManager::ROUNDED_SQUARE,          "Images/Rounded_Square.png"},
                    {ResourcesManager::CURVE_POINT,             "Images/Curve_Point.png"},
                    {ResourcesManager::CURVE_POINT_PRESSED,     "Images/Curve_Point_PR.png"},
                    {ResourcesManager::START_PAINT_BACK,        "Images/PaintBack.png"},
            };

    ResourcesManager::ResourceItem<ResourcesManager::StandardFonts> standard_font_items[ResourcesManager::STANDARD_FONTS_COUNT]
            {
                    {ResourcesManager::PRO_DISPLAY,   "Fonts/SF-Pro-Display-Regular.otf"},
                    {ResourcesManager::PRO_TEXT,      "Fonts/SF-Pro-Text-Bold.otf"}
            };
};

#endif
