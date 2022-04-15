#ifndef CANVAS_H
#define CANVAS_H

#include <SFML/Graphics.hpp>
#include "../Utils/Color.h"
#include "../Utils/Vector2.h"

class Canvas{
public:
    Canvas();

    Canvas(const char *window_name, size_t width, size_t height);

    void ClearScreen();
    void Display();

    sf::RenderWindow& GetWindow();
    double GetDeltaTime();
    double GetGlobalTime();
    size_t GetScreeHeight() const;
    size_t GetScreeWidth()  const;

    void SetFpsLimit(unsigned limit);

private:
    sf::RenderWindow window;
    sf::Clock update_clock, global_clock;

    size_t screen_width, scree_height;
};

#endif
