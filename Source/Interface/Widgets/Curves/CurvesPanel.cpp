
#include "CurvesPanel.h"

CurvesPanel::CurvesPanel(Widget *_parent, Vector2I _local_position)
        : Panel(_parent, _local_position, PanelWidth, PanelHeight, StandardName) {

    new CurvesField(this, CurvesFieldPos, CurvesFieldWidth, CurvesFieldHeight);
}

void CurvesPanel::OnDelete() {
    Panel::OnDelete();
    ApplicationPtr->logic_manager->isPanelOpen[LogicManager::CURVES] = false;
}
