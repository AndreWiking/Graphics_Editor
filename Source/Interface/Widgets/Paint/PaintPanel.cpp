
#include "PaintPanel.h"

PaintPanel::PaintPanel(Widget *_parent, Vector2I _local_position)
        : Panel(_parent, _local_position, PanelWidth, PanelHeight, StandardName) {

    new PaintCanvas(this, PaintCanvasPos, PaintCanvasWidth, PaintCanvasHeight);

}

void PaintPanel::OnDelete() {
    Panel::OnDelete();
    ApplicationPtr->logic_manager->isPanelOpen[LogicManager::PAINT_CANVAS] = false;
}
