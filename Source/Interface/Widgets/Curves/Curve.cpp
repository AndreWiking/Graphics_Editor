
#include "Curve.h"

Curve::Curve(const std::list<CurvePoint *> &curve_points, size_t _canvas_width, size_t _canvas_height)
        : canvas_width(_canvas_width), canvas_height(_canvas_height) {

    for (const CurvePoint* point : curve_points)
        points.push_back(point->GetLocalCentrePosition());

    std::sort(points.begin(), points.end(), [](const Vector2F &a, const Vector2F &b) { return a.X < b.X; });

    if (!points.empty() && points.front().X != 0) {
        points.insert(points.begin(), Vector2F(0, points.front().Y));
    }
    if (!points.empty() && points.back().X != canvas_width) {
        points.push_back(Vector2F(canvas_width, points.back().Y));
    }

    CalculateRenderPoints();
}

void Curve::Draw(sf::RenderTexture &curves_canvas, double thickness, Color color) {
    for (int i = 0; i + 1 < RenderPointsCount; ++i) {
        DrawLine(&curves_canvas, canvas_height, render_points[i], render_points[i + 1], thickness, color);
        //DrawCircle(&curves_canvas, canvas_height, render_points[i], 1, {0, 255, 0});
    }
}

bool Curve::isNewPointPos(Vector2F pos, double line_dist, double no_spawn_dist) {
    for (Vector2F point : points)
        if ((point - pos).SquareLength() < no_spawn_dist * no_spawn_dist)
            return false;

    for (int i = 0; i < RenderPointsCount; ++i)
        if ((render_points[i] - pos).SquareLength() < line_dist * line_dist)
            return true;

    return false;
}

void Curve::SetRGB_Transformation() {
    for (int i = 0; i < RenderPointsCount; ++i)
        Settings->RGB_Transformation[i] = (canvas_height - render_points[i].Y) / canvas_height * UINT8_MAX;
}

void Curve::CalculateRenderPoints() {
    double delta = (double)canvas_width / RenderPointsCount;
    double curX = 0;
    size_t num = 0;
    for (int i = 0; i + 1 < points.size(); ++i){
        while (curX < points[i + 1].X + Vector2F::delta && num < RenderPointsCount){
            double coeff = (curX - points[i].X) / (points[i + 1].X - points[i].X);
            if (i == 0 || i + 2  == points.size())
                render_points[num++] = GetLinearPoint(points[i], points[i + 1], coeff);
            else
                render_points[num++] = CatmullRom(points[i - 1], points[i], points[i + 1], points[i + 2],
                                                  coeff , CatmullRomAlpha);
            curX += delta;
        }
    }

    if (num != RenderPointsCount)
        std::cerr << "Not all points set\n";

    SetRGB_Transformation();
}
