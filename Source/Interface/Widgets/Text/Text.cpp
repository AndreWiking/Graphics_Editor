
#include "Text.h"

Text::Text(Widget *_parent, Vector2I _local_position, size_t font_id, const std::string &title, Color _text_color,
           Color text_outline_color, float outline_thickness, unsigned int _character_size) :
           Widget(_parent, _local_position), text_color(_text_color) {

    text.setFont(ApplicationPtr->resources_manager->GetFont(font_id));
    text.setString(title);
    text.setFillColor(text_color);
    text.setOutlineColor(text_outline_color);
    text.setOutlineThickness(outline_thickness);
    text.setCharacterSize(_character_size);
    UpdateTextOrigin();
}

Text::Text(Widget *_parent, Vector2I _local_position, size_t font_id, const std::string &title, Color _text_color,
           unsigned int _character_size) :
           Text(_parent, _local_position, font_id, title, _text_color, {}, 0, _character_size) {}

void Text::Draw(sf::RenderWindow *window) {
    window->draw(text);
}

void Text::SetCentrePos() {
    SetLocalPosition(Vector2I(parent->GetWidth() / 2, parent->GetHeight() / 2));
}

sf::Text *Text::GetTextPtr() { return &text; }

Color Text::GetColor() const { return text_color; }

void Text::UpdateTextOrigin() {
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top  + textRect.height / 2.0f);
}

void Text::UpdatePos() {
    text.setPosition(GetGlobalPosition());
}

void Text::SetString(std::string string) {
    text.setString(string);
}

void Text::BestSize(double max_width) {
    sf::FloatRect textRect = text.getLocalBounds();
    double scale = max_width / textRect.width * ScaleCoeff;
    text.setScale(scale, scale);
    NormalScale = {scale, scale};
}

