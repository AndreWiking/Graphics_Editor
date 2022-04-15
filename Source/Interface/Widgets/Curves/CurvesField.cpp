
#include "CurvesField.h"

CurvesField::CurvesField(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height)
        : Widget(_parent, _local_position, _width, _height) {

    if (!curves_canvas.create(width, height)) {} // todo: error

    curves_canvas.clear(BackgroundColor);

    sprite.setTexture(curves_canvas.getTexture());

    Gui_Manager->AddSubscribedWidget(this, GuiManager::ON_MOUSE_MOVED);

    if (ApplicationPtr->logic_manager->Saved_curve_points_pos == nullptr) {
        ApplicationPtr->logic_manager->Saved_curve_points_pos = new std::list<Vector2I>;
        ResetCurve();
    }
    else
        LoadSavedCurve();
}

void CurvesField::Draw(sf::RenderWindow *window) {
    curves_canvas.clear(BackgroundColor);
    DrawCurve();
    Widget::Draw(window);
}

void CurvesField::OnGlobalMouseMoved(Mouse global_mouse) {
    for (auto it = curve_points.begin(); it != curve_points.end();) {
        CurvePoint* point = *it;
        bool isDelete = false;
        if (point->is_moving) {
            if (isPosInside(point->GetLocalCentrePosition())) {
                point->MoveToPosition(global_mouse.position - GetGlobalPosition() - point->move_offset);
            }
            else {
                point->SetDelete();
                it = curve_points.erase(point->curve_points_it);
                curve_points_pos.erase(point->curve_points_pos_it);
                isDelete = true;
            }
        }
        if (!isDelete) ++it;
    }

    Settings->ApplyRGB_Transformation = true;

    if (curve_points.empty())
        ResetCurve();
    else
        UpdateCurve();
}

void CurvesField::OnPressBegin(Mouse mouse) {
    if (rgb_curve.isNewPointPos(mouse.position, NewPointMinDist, NewPointMaxNoSpawnDist)){
        AddPoint(mouse.position);
    }
}

void CurvesField::ResetCurve() {
    curve_points.clear();

    AddPoint(Vector2I(0, height));
    AddPoint(Vector2I(width, 0));

    UpdateCurve();
}

void CurvesField::AddPoint(Vector2I pos) {
    curve_points.push_back(new CurvePoint(this, {}));
    curve_points.back()->curve_points_it = std::prev(curve_points.end());
    curve_points.back()->SetLocalCentrePosition(pos);

    curve_points_pos.push_back(pos);
    curve_points.back()->curve_points_pos_it = std::prev(curve_points_pos.end());
}

void CurvesField::UpdateCurve() {
    rgb_curve = Curve(curve_points, width, height);
}

void CurvesField::DrawCurve() {
    //UpdateCurve();
    rgb_curve.Draw(curves_canvas, CurveThickness, CurveColor);
}

void CurvesField::SaveCurve() {
    *ApplicationPtr->logic_manager->Saved_curve_points_pos = curve_points_pos;
}

void CurvesField::LoadSavedCurve() {
    
    for (const Vector2I &pos : *ApplicationPtr->logic_manager->Saved_curve_points_pos)
        AddPoint(pos);

    UpdateCurve();
}

void CurvesField::OnDelete() {
    Widget::OnDelete();
    SaveCurve();
}
