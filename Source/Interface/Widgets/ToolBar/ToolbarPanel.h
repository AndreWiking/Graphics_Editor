
#ifndef TOOLBAR_PANEL_H
#define TOOLBAR_PANEL_H


#include "../Panels/Panel.h"
#include "ToolWidget.h"


class ToolbarPanel : public Panel{
public:
    ToolbarPanel(Widget* _parent, Vector2I _local_position);

    void OnDelete() override;

protected:
    static constexpr char StandardName[] = "Toolbar";
    static constexpr size_t StandardWidth = 350;
    static constexpr size_t StandardHeightBounds = 70;

    static constexpr Vector2I ToolStartPos = {20, 80};
    static constexpr Vector2I ToolDeltaPos = {0, 120};

    size_t GetNormalHeight();
};


#endif
