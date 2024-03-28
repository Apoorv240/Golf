#pragma once

#include <stdbool.h>

extern double bounds(double low, double high, double num);
extern bool inBounds(double low, double high, double num);

struct {
    double magnitude;
    double theta;
} typedef Vector;

extern double vectorCalcY(Vector v);
extern double vectorCalcX(Vector v);
extern double vectorCalcTheta(double x, double y);