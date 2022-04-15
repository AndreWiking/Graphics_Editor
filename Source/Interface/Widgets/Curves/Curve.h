
#ifndef CURVE_H
#define CURVE_H

#include "../../../Utils/CatmullRom.h"
#include "CurvePoint.h"
#include "../../../Utils/Utils2D.h"

class Curve{
public:
    Curve() {}

    Curve(const std::list<CurvePoint*> &curve_points, size_t _canvas_width, size_t _canvas_height);


    void Draw(sf::RenderTexture &curves_canvas, double thickness, Color color);

    bool isNewPointPos(Vector2F pos, double line_dist, double no_spawn_dist);

    void SetRGB_Transformation();

private:

    static constexpr size_t RenderPointsCount = sizeof(Settings->RGB_Transformation) /
                                                sizeof(Settings->RGB_Transformation[0]);

    static constexpr double CatmullRomAlpha = 0.5;

    std::vector<Vector2F> points;
    Vector2F render_points[RenderPointsCount];
    size_t canvas_width, canvas_height;


    void CalculateRenderPoints();
};


#endif //CURVE_H
