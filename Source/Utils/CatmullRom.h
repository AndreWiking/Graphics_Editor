
#ifndef CATMULL_ROM_H
#define CATMULL_ROM_H

#include "Vector2.h"

//double GetKnot(double t, double alpha, Vector2F p0, Vector2F p1);

Vector2F CatmullRom(Vector2F p0, Vector2F p1, Vector2F p2, Vector2F p3, double coeff, double alpha);


Vector2F GetLinearPoint(Vector2F point1, Vector2F point2, double coeff);


#endif
