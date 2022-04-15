
#include "CatmullRom.h"

static const double AlphaCoeff = 0.5;

double GetKnot(double t, double alpha, Vector2F p0, Vector2F p1) {
    return t + pow((p1 - p0) % (p1 - p0), alpha * AlphaCoeff);
}

Vector2F CatmullRom(Vector2F p0, Vector2F p1, Vector2F p2, Vector2F p3, double coeff, double alpha) {
    double t0 = 0.0;
    double t1 = GetKnot(t0, alpha, p0, p1);
    double t2 = GetKnot(t1, alpha, p1, p2);
    double t3 = GetKnot(t2, alpha, p2, p3);
    coeff = t1 + (t2 - t1) * coeff;
    Vector2F a1 = p0 * ((t1 - coeff) / (t1 - t0)) + p1 * ((coeff - t0) / (t1 - t0));
    Vector2F a2 = p1 * ((t2 - coeff) / (t2 - t1)) + p2 * ((coeff - t1) / (t2 - t1));
    Vector2F a3 = p2 * ((t3 - coeff) / (t3 - t2)) + p3 * ((coeff - t2) / (t3 - t2));
    Vector2F b1 = a1 * ((t2 - coeff) / (t2 - t0)) + a2 * ((coeff - t0) / (t2 - t0));
    Vector2F b2 = a2 * ((t3 - coeff) / (t3 - t1)) + a3 * ((coeff - t1) / (t3 - t1));
    Vector2F c1 = b1 * ((t2 - coeff) / (t2 - t1)) + b2 * ((coeff - t1) / (t2 - t1));
    return c1;
}

Vector2F GetLinearPoint(Vector2F point1, Vector2F point2, double coeff) {
    return point1 + (point2 - point1) * coeff;
}
