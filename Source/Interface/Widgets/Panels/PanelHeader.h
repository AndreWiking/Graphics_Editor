
#ifndef PANEL_HEADER_H
#define PANEL_HEADER_H

#include "../Image.h"
#include "../../Controllers/GuiManager.h"

//#define PANEL_HEADER_DEBUG

extern GuiManager *Gui_Manager;

class PanelHeader : public Image {
public:
    PanelHeader(Widget* _parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id);

protected:
    Widget* panel;
    bool is_moving = false;
    Vector2I start_moving_mouse_global_pos;
    Vector2I start_moving_panel_local_pos;

    void OnPressBegin(Mouse mouse) override;

    void OnPressEnd(bool is_inside, Mouse mouse) override;

    void OnGlobalMouseMoved(Mouse global_mouse) override;
};

#endif
