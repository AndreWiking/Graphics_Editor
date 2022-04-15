
#ifndef PAINT_CANVAS_H
#define PAINT_CANVAS_H

#include "../Widget.h"
#include "../../../Utils/Utils2D.h"

class PaintCanvas : Widget{
public:
    PaintCanvas(Widget* _parent, Vector2I _local_position, size_t _width, size_t _height);

    ~PaintCanvas() override;

    void OnPressBegin(Mouse mouse) override;

    void OnPressEnd(bool is_inside, Mouse mouse) override;

    void OnMouseOut(Mouse mouse) override;

    void OnMouseIn(Mouse mouse) override;

    void OnMouseMoved(Mouse mouse) override;

    void Draw(sf::RenderWindow *window) override;

protected:
    static constexpr ResourcesManager::StandardTextures start_back_texture = ResourcesManager::START_PAINT_BACK;
    sf::RenderTexture paint_canvas_texture, paint_canvas_preview_texture;
    bool is_drawing = false, first_draw = true;
    Vector2I prev_draw_pos;
    static constexpr Color BackgroundColor = GlobalSettings::BackgroundColor;
    sf::Texture corrected_texture;


    void ApplyColorCorrection();


};

void WorkEffect(Effect *effect);
void WorkToolOnPress(Tool *tool, Vector2I pos);
void WorkToolOnRelease(Tool *tool, Vector2I pos);
void WorkToolOnMove(Tool *tool, Vector2I old_pos, Vector2I new_pos);

#endif
