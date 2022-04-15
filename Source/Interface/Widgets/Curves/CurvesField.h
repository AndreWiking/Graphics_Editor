
#ifndef CURVES_FIELD_H
#define CURVES_FIELD_H


#include "Curve.h"
#include "../../../Utils/Utils2D.h"
#include "../../Controllers/GuiManager.h"

extern GuiManager *Gui_Manager;

class CurvesField : Widget {
public:

    CurvesField(Widget *_parent, Vector2I _local_position, size_t _width, size_t _height);

    void Draw(sf::RenderWindow *window) override;

    void OnGlobalMouseMoved(Mouse global_mouse) override;

    void OnPressBegin(Mouse mouse) override;

    void OnDelete() override;

protected:
    sf::RenderTexture curves_canvas;
    std::list<CurvePoint*> curve_points;
    std::list<Vector2I> curve_points_pos;
    Curve rgb_curve;


    static constexpr double CurveThickness = 3;
    static constexpr Color CurveColor = {100, 100, 80};
    static constexpr Color BackgroundColor = GlobalSettings::BackgroundColor;
    static constexpr double NewPointMinDist = 10, NewPointMaxNoSpawnDist = 22;
private:

    void ResetCurve();

    void AddPoint(Vector2I pos);

    void UpdateCurve();

    void DrawCurve();

    void SaveCurve();
    void LoadSavedCurve();

};


#endif
