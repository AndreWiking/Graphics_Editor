
#ifndef OPEN_PANEL_BUTTON_H
#define OPEN_PANEL_BUTTON_H


#include "Button.h"
#include "../Brush/BrushPanel.h"
#include "../Paint/PaintCanvas.h"
#include "../ColorPicker/ColorPickerPanel.h"
#include "../Paint/PaintPanel.h"
#include "../Curves/CurvesPanel.h"
#include "../ToolBar/ToolbarPanel.h"

class OpenPanelButton : public Button {
public:
    OpenPanelButton(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height,
                          LogicManager::OpenPanel _open_panel_type);

    void OnClicked() override;

protected:

    Panel *open_panel[LogicManager::OPEN_PANEL_COUNT];
    LogicManager::OpenPanel open_panel_type;

    static constexpr Vector2I OpenPanelPos[LogicManager::OPEN_PANEL_COUNT] = {{400, 70}, {1900, 70}, {1900, 350}, {35, 880},
                                                                              {1805, 700}};

    static constexpr size_t TextSize = 50;
    static const char *Names[LogicManager::OPEN_PANEL_COUNT];

private:

    void OpenPanel(LogicManager::OpenPanel type);

};


#endif
