
#include "Effect.h"

void Effect::Apply() {

    if (Settings->Paint_canvas_preview_texture != nullptr && Settings->Paint_canvas_texture != nullptr) {

        Settings->Paint_canvas_preview_texture->clear({0, 0, 0, 0});
        (*PluginInterface->effect.apply)();

        sf::Sprite sprite(Settings->Paint_canvas_preview_texture->getTexture());
        sprite.setPosition(0, 0);

        Settings->Paint_canvas_texture->draw(sprite);
    }
}
