
#include "PanelHeader.h"

PanelHeader::PanelHeader(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height, size_t _texture_id) :
        Image(_parent, _local_position, _width, _height, _texture_id), panel(parent){

    Gui_Manager->AddSubscribedWidget(this, GuiManager::ON_MOUSE_MOVED);
}

void PanelHeader::OnPressBegin(Mouse mouse) {
    is_moving = true;
    start_moving_mouse_global_pos = GetPosInGlobal(mouse.position);
    start_moving_panel_local_pos = panel->GetLocalPosition();

#ifdef PANEL_HEADER_DEBUG
    mouse.PrintInfo();
#endif
}

void PanelHeader::OnPressEnd(bool is_inside, Mouse mouse) {
    is_moving = false;

#ifdef PANEL_HEADER_DEBUG
    mouse.PrintInfo();
#endif
}

void PanelHeader::OnGlobalMouseMoved(Mouse global_mouse) {
    if (is_moving){
        panel->SetLocalPosition(start_moving_panel_local_pos + global_mouse.position - start_moving_mouse_global_pos);
    }

#ifdef PANEL_HEADER_DEBUG
    global_mouse.PrintInfo();
#endif
}
