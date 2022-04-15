
#include "Color.h"

Color::operator sf::Color() const {
    return sf::Color(R, G, B, A);
}

Color::operator PRGBA() const {
    return PRGBA(R, G, B, A);
}

std::string Color::GetRGB_String() {
    return "( " + std::to_string(R) + ", " + std::to_string(G) + ", " + std::to_string(B) + ")";
}

unsigned char& Color::operator[](int type) {
    switch (type % ChannelCount) {
        case 0: return R;
        case 1: return G;
        case 2: return B;
        case 3: return A;
    }
    return A;
}

Color::Color(sf::Color _color) : R(_color.r), G(_color.g), B(_color.b), A(_color.a) {}
Color::Color(PRGBA _color) : R(_color.r), G(_color.g), B(_color.b), A(_color.a) {}

Color MergeColors(Color col1, double coeff1, Color col2,  double coeff2) {
    coeff1 /= (coeff1 + coeff2);
    coeff2 = 1.0 - coeff1;
    return Color(round(col1.R * coeff1 + col2.R * coeff2),
                 round(col1.G * coeff1 + col2.G * coeff2),
                 round(col1.B * coeff1 + col2.B * coeff2));
}

Color MergeTextColors(Color colText, Color colMask) {

    return Color(round(colText.R * (colMask.R / 255.0)),
                 round(colText.G * (colMask.G / 255.0)),
                 round(colText.B * (colMask.B / 255.0)));
}
