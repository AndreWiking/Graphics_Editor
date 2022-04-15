
#include "OpenPanelButton.h"

const char *OpenPanelButton::Names[LogicManager::OPEN_PANEL_COUNT] = {"Paint Canvas", "Brush Size", "Color Picker", "Toolbar",
                                                                      "Curves"};

OpenPanelButton::OpenPanelButton(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height,
                                 LogicManager::OpenPanel _open_panel_type)
        : Button(_parent, _local_position, _width, _height, ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_DARK),
                 ApplicationPtr->resources_manager->GetTextureId(ResourcesManager::BUTTON_DARK)), open_panel_type(_open_panel_type) {

    Text *text = new Text(this, {}, ApplicationPtr->resources_manager->GetFontId(ResourcesManager::PRO_DISPLAY),
                          Names[open_panel_type], GlobalSettings::BlackButtonTextColor, TextSize);
    this->SetText(text);
}

void OpenPanelButton::OnClicked() {
    if (!ApplicationPtr->logic_manager->isPanelOpen[open_panel_type]){
        ApplicationPtr->logic_manager->isPanelOpen[open_panel_type] = true;
        OpenPanel(open_panel_type);
        open_panel[open_panel_type]->SetFirstInChildren();
        Gui_Manager->GetRoot()->UpdateChildrenPos();
    }
    else if (open_panel[open_panel_type] != nullptr){

        open_panel[open_panel_type]->SetFirstInChildren();
    }
}

void OpenPanelButton::OpenPanel(LogicManager::OpenPanel type) {
    switch (type) {
        case LogicManager::BRUSH_SIZE:
            open_panel[type] = new BrushPanel(Gui_Manager->GetRoot(), OpenPanelPos[type]);
            break;
        case LogicManager::PAINT_CANVAS:
            open_panel[type] = new PaintPanel(Gui_Manager->GetRoot(), OpenPanelPos[type]);
            Settings->ApplyRGB_Transformation = true;
            break;
        case LogicManager::COLOR_PICKER:
            open_panel[type] = new ColorPickerPanel(Gui_Manager->GetRoot(), OpenPanelPos[type]);
            break;
        case LogicManager::CURVES:
            open_panel[type] = new CurvesPanel(Gui_Manager->GetRoot(), OpenPanelPos[type]);
            Settings->UseRGB_Transformation = true;
            break;
        case LogicManager::TOOLBAR:
            open_panel[type] = new ToolbarPanel(Gui_Manager->GetRoot(), OpenPanelPos[type]);
            break;
        case LogicManager::OPEN_PANEL_COUNT:
            break;
    }
}
