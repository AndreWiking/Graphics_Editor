
#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <cstdio>
#include <SFML/Graphics.hpp>
#include "../../Utils/Color.h"

class GlobalSettings {
public:
    static GlobalSettings *Instance();
    static bool DeleteInstance();

    Color BrushColor = Color(100, 120, 40);
    double BrushSize = 25.0;

    unsigned char RGB_Transformation[UINT8_MAX + 1];
    bool UseRGB_Transformation = false;
    bool ApplyRGB_Transformation = true;
    sf::RenderTexture *Paint_canvas_texture = nullptr;
    sf::RenderTexture *Paint_canvas_preview_texture = nullptr;
    sf::Clock GlobalClock = {};

    static constexpr Color StandardTextColor =          Color(235, 235, 245, 153);
    static constexpr Color StandardTextOutlineColor =   Color(255, 255, 255);
    static constexpr Color BlackButtonTextColor =       Color(223, 222, 223);
    static constexpr Color WhiteButtonTextColor =       Color(61, 61, 61);
    static constexpr Color BlueButtonTextColor =        Color(225, 234, 248);

    static constexpr Color BackgroundColor =            Color(55, 55, 55);

    static constexpr float StandardTextOutlineThickness = 0.0;
private:
    static GlobalSettings *_self;

    GlobalSettings() {}

    ~GlobalSettings() {}
};

#endif //GLOBAL_SETTINGS_H
