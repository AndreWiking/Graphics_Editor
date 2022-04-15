
#ifndef CURVES_PANEL_H
#define CURVES_PANEL_H


#include "../Panels/Panel.h"
#include "CurvesField.h"

class CurvesPanel : public Panel {
public:

    CurvesPanel(Widget* _parent, Vector2I _local_position);

    void OnDelete() override;

protected:

    static constexpr char StandardName[] = "Curves";
    static constexpr size_t PanelWidth = 750;
    static constexpr size_t PanelHeight = 800;

    static constexpr Vector2I CurvesFieldPos  = {25, 75};
    static constexpr size_t CurvesFieldWidth  = 700;
    static constexpr size_t CurvesFieldHeight = 700;
};


#endif
