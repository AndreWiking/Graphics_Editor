
#ifndef RESOURCES_MANAGER_H
#define RESOURCES_MANAGER_H

#include <iostream>
#include <vector>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

class ResourcesManager {
public:
    static ResourcesManager *Instance();
    static bool DeleteInstance();

    template<typename T>
    class ResourceItem{
    public:
        T type;
        const char *path;
    };

    enum StandardTextures {
        BACKGROUND = 0,
        HEADER, PANEL, CLOSE_BUTTON, CLOSE_PRESSED_BUTTON,
        SLIDER_KNOB, SLIDER_BACK_H, SLIDER_ROUNDED_H,
        SLIDER_BACK_V, SLIDER_ROUNDED_V,
        BUTTON_DARK,
        BUTTON_WHITE,
        BUTTON_BLUE,
        RGB_KNOB,
        RGB_KNOB_PRESSED,
        RGB_LINE,
        RGB_ROUNDED_LINE,
        ROUNDED_SQUARE,
        CURVE_POINT,
        CURVE_POINT_PRESSED,
        START_PAINT_BACK,
        STANDARD_TEXTURES_COUNT
    };

    enum StandardFonts {
        PRO_DISPLAY = 0, PRO_TEXT,
        STANDARD_FONTS_COUNT
    };

    void LoadStandardFonts(const ResourceItem<StandardFonts> *font_items, size_t count);

    void LoadStandardTextures(const ResourceItem<StandardTextures> *texture_items, size_t count);

    size_t AddTexture(const char* path);

    size_t AddFont(const char *path);

    sf::Texture& GetTexture(size_t id);

    sf::Font& GetFont(size_t id);

    size_t GetTextureId(StandardTextures type) const;

    size_t GetFontId(StandardFonts type) const;

    static constexpr size_t zero_texture_id = 0, zero_font_id = 0;

private:
    static ResourcesManager *_self;

    ResourcesManager(){
        textures.push_back(sf::Texture());
        fonts.push_back(sf::Font());
    }
    virtual ~ResourcesManager() {}


    std::vector<sf::Texture> textures;
    std::vector<sf::Font> fonts;

    size_t standard_textures_id[STANDARD_TEXTURES_COUNT];
    size_t standard_font_id[STANDARD_FONTS_COUNT];

};

#endif //RESOURCES_MANAGER_H
