
#include "PaintCanvas.h"

PaintCanvas::PaintCanvas(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height) :
        Widget(_parent, _local_position, _width, _height) {

    paint_canvas_texture.create(width, height);

    paint_canvas_texture.clear(BackgroundColor);

    sprite.setTexture(paint_canvas_texture.getTexture());
    sf::Sprite back(ApplicationPtr->resources_manager->GetTexture(
                    ApplicationPtr->resources_manager->GetTextureId(start_back_texture)));
    back.setPosition(0, 0);
    back.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
    back.setScale(1, -1);
    back.setPosition(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
    paint_canvas_texture.draw(back);

    paint_canvas_preview_texture.create(width, height);
    paint_canvas_preview_texture.clear({0,0,0,0});

    Settings->Paint_canvas_texture = &paint_canvas_texture;
    Settings->Paint_canvas_preview_texture = &paint_canvas_preview_texture;
}

PaintCanvas::~PaintCanvas() {
    Settings->Paint_canvas_texture = nullptr;
    Settings->Paint_canvas_preview_texture = nullptr;
}

void WorkEffect(Effect *effect){
    if (effect != nullptr){
        effect->Apply();
        //ApplicationPtr->tool_bar->ResetActiveEffect();
    }
}

void WorkToolOnPress(Tool *tool, Vector2I pos){
    if (tool != nullptr) {
        Settings->Paint_canvas_preview_texture->clear({0, 0, 0, 0});
        (*tool->PluginInterface->tool.on_press)(PVec2f(pos.X, pos.Y));
    }
}

void PaintCanvas::OnPressBegin(Mouse mouse) {
    is_drawing = true;
    first_draw = true;

    Effect *effect = ApplicationPtr->tool_bar->GetActiveEffect();
    Tool *tool = ApplicationPtr->tool_bar->GetActiveTool();

    WorkEffect(effect);
    WorkToolOnPress(tool, mouse.position);
}

void WorkToolOnRelease(Tool *tool, Vector2I pos){
    if (tool != nullptr){
        (*tool->PluginInterface->tool.on_release)(PVec2f(pos.X, pos.Y));

        if (Settings->Paint_canvas_preview_texture != nullptr && Settings->Paint_canvas_texture != nullptr) {
            sf::Sprite sprite(Settings->Paint_canvas_preview_texture->getTexture());
            sprite.setPosition(0, 0);

            Settings->Paint_canvas_texture->draw(sprite);
        }

    }
}

void PaintCanvas::OnPressEnd(bool is_inside, Mouse mouse) {
    is_drawing = false;
    first_draw = true;

    Tool *tool = ApplicationPtr->tool_bar->GetActiveTool();
    WorkToolOnRelease(tool, mouse.position);
}

void PaintCanvas::OnMouseOut(Mouse mouse) {
    first_draw = true;

    if (is_drawing)
        DrawLine(&paint_canvas_texture, height, prev_draw_pos, mouse.position, Settings->BrushSize,
                 Settings->BrushColor);
}

void PaintCanvas::OnMouseIn(Mouse mouse) {
    if (is_drawing) {
        prev_draw_pos = mouse.position;
    }
}

void WorkToolOnMove(Tool *tool, Vector2I old_pos, Vector2I new_pos){
    if (tool != nullptr){
        (*tool->PluginInterface->tool.on_move)(PVec2f(old_pos.X, old_pos.Y), PVec2f(new_pos.X, new_pos.Y));
    }
}

void PaintCanvas::OnMouseMoved(Mouse mouse) {

    Tool *tool = ApplicationPtr->tool_bar->GetActiveTool();
    WorkToolOnMove(tool, prev_draw_pos, mouse.position);
    Effect *effect = ApplicationPtr->tool_bar->GetActiveEffect();

    if (is_drawing) {
        if (first_draw) {
            prev_draw_pos = mouse.position;
            first_draw = false;
            if (tool == nullptr && effect == nullptr)
                DrawCircle(&paint_canvas_texture, height, prev_draw_pos, Settings->BrushSize / 2, Settings->BrushColor);
        }
        else {
            if (tool == nullptr && effect == nullptr)
                DrawLine(&paint_canvas_texture, height, prev_draw_pos, mouse.position, Settings->BrushSize,
                         Settings->BrushColor);
            prev_draw_pos = mouse.position;
        }
        if (Settings->UseRGB_Transformation)
            Settings->ApplyRGB_Transformation = true;
    }
}

void PaintCanvas::Draw(sf::RenderWindow *window) {

    if (Settings->UseRGB_Transformation) {
        if (Settings->ApplyRGB_Transformation) {
            Settings->ApplyRGB_Transformation = false;
            ApplyColorCorrection();

        }
        sprite.setTexture(corrected_texture);
    }
    else {
        sprite.setTexture(paint_canvas_texture.getTexture());
    }

    window->draw(sprite);
}

void PaintCanvas::ApplyColorCorrection() {
    sf::Image canvas_image = paint_canvas_texture.getTexture().copyToImage();

    for (size_t y = 0; y <  canvas_image.getSize().y; ++y)
        for (size_t x = 0; x <  canvas_image.getSize().x; ++x) {
            Color old(canvas_image.getPixel(x, y));
            canvas_image.setPixel(x, y, Color(Settings->RGB_Transformation[old.R],
                                              Settings->RGB_Transformation[old.G],
                                              Settings->RGB_Transformation[old.B], old.A));
        }

    corrected_texture.loadFromImage(canvas_image);

}


