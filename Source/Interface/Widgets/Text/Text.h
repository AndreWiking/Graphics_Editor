
#ifndef TEXT_H
#define TEXT_H

#include "../Widget.h"

class Text : public Widget{
public:

    Text(Widget* _parent, Vector2I _local_position, size_t font_id, const std::string &title, Color _text_color,
         Color text_outline_color, float outline_thickness, unsigned _character_size);

    Text(Widget* _parent, Vector2I _local_position, size_t font_id, const std::string &title, Color _text_color,
         unsigned _character_size);

    void Draw(sf::RenderWindow *window) override;

    void SetCentrePos();

    sf::Text* GetTextPtr();

    Color GetColor() const;

    void SetString(std::string string);

    void BestSize(double max_width);

    Vector2F NormalScale = {1, 1};
protected:
    sf::Text text;
    Color text_color;

    static constexpr double ScaleCoeff = 0.8;

    void UpdateTextOrigin();

    void UpdatePos() override;
};


#endif
