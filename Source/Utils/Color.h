#ifndef COLOR_H
#define COLOR_H

#include <cstdint>
#include <cmath>
#include <string>
#include <sstream>
#include <SFML/Graphics/Color.hpp>
#include <plugin_std.h>

class Color{
public:
    unsigned char R, G, B, A;
    Color() : R(0), G(0), B(0), A(UINT8_MAX){};
    constexpr Color(unsigned char r, unsigned char g, unsigned char b) : R(r), G(g), B(b), A(255) {}
    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) : R(r), G(g), B(b), A(a) {}
    Color (sf::Color _color);
    Color (PRGBA _color);

    unsigned char& operator[](int type);

    operator sf::Color() const;
    operator PRGBA() const;

    std::string GetRGB_String();

    std::string GetHEX_String(){
        int res = (R << 16) + (G << 8) + B;
        std::stringstream stream;
        stream << std::hex << res;
        return "#" + stream.str();
    }

private:
    static constexpr int ChannelCount = 4;
};

Color MergeColors(Color col1, double coeff1, Color col2,  double coeff2);
Color MergeTextColors(Color colText, Color colMask);

#endif
