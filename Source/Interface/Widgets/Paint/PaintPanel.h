
#ifndef PAINT_PANEL_H
#define PAINT_PANEL_H

#include "../Panels/Panel.h"
#include "PaintCanvas.h"

class PaintPanel : public Panel {
public:

    PaintPanel(Widget* _parent, Vector2I _local_position);

    void OnDelete() override;

protected:

    static constexpr char StandardName[] = "Paint";
    static constexpr size_t PanelWidth = 1400;
    static constexpr size_t PanelHeight = 1450;

    static constexpr Vector2I PaintCanvasPos = {25, 75};
    static constexpr size_t PaintCanvasWidth = 1350;
    static constexpr size_t PaintCanvasHeight = 1350;

};

#endif
