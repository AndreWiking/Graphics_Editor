
#include "Canvas.h"

Canvas::Canvas(){

}

Canvas::Canvas(const char *window_name, size_t width, size_t height){
    scree_height = height;
    screen_width = width;
    window.create(sf::VideoMode(screen_width, scree_height), window_name);
    update_clock = sf::Clock();
    global_clock = sf::Clock();
}

void Canvas::ClearScreen() {
    window.clear();
}

void Canvas::Display() {
    window.display();
}


sf::RenderWindow& Canvas::GetWindow(){
    return window;
}

double Canvas::GetDeltaTime() {
    return update_clock.restart().asSeconds();
}

double Canvas::GetGlobalTime() {
    return global_clock.getElapsedTime().asSeconds();
}

size_t Canvas::GetScreeHeight() const {
    return scree_height;
}

size_t Canvas::GetScreeWidth() const {
    return screen_width;
}

void Canvas::SetFpsLimit(unsigned int limit) {
    window.setFramerateLimit(limit);
}

//void DrawRectangle(sf::RenderWindow *window, Vector2F cornerLeftTop, Vector2F cornerRightDown, Color color) {
//    sf::RectangleShape rectangle(cornerRightDown - cornerLeftTop);
//    rectangle.setPosition(cornerLeftTop);
//    rectangle.setFillColor(color);
//    window->draw(rectangle);
//}
//
//void DrawRectangle(sf::RenderTexture *texture, Vector2F cornerLeftTop, Vector2F cornerRightDown, Color color) {
//    sf::RectangleShape rectangle(cornerRightDown - cornerLeftTop);
//    rectangle.setPosition(cornerLeftTop);
//    rectangle.setFillColor(color);
//    texture->draw(rectangle);
//}
