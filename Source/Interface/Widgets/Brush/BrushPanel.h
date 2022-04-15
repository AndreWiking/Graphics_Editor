
#ifndef BRUSH_PANEL_H
#define BRUSH_PANEL_H

#include "../Panels/Panel.h"
#include "BrushSlider.h"
#include "AddBrushSizeButton.h"

class BrushPanel : public Panel {
public:

    BrushPanel(Widget* _parent, Vector2I _local_position);

    void OnDelete() override;

protected:
    static constexpr char StandardName[] = "Brush";
    static constexpr size_t PanelWidth = 550;
    static constexpr size_t PanelHeight = 250;
    static constexpr size_t StandardLength = 450;
    static constexpr size_t StandardHeight = 8;

    static constexpr Vector2I AddPlusButtonPos = {50, 150};
    static constexpr Vector2I AddMinusButtonPos = {400, 150};
    static constexpr Vector2I SliderPos = {50, 100};
    static constexpr Vector2I TextDisplayPos = {245, 150};

    static constexpr size_t AddButtonWidth  = 120;
    static constexpr size_t AddButtonHeight = 80;

    static constexpr size_t StandardTextSize = 60;

};


#endif
