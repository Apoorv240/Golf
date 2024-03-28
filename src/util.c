#include "util.h"
#include <math.h>

double bounds(double low, double high, double num) {
    if (num < low) return low;
    if (num > high) return high;
    return num;
}

bool inBounds(double low, double high, double num) {
    if ((num <= high) && (num >= low)) return true;
    return false;
}

double vectorCalcX(Vector v) {
    return v.magnitude * cos(v.theta * M_PI / 180);
}
double vectorCalcY(Vector v) {
    return v.magnitude * sin(v.theta * M_PI / 180);
}

double vectorCalcTheta(double x, double y) {
    double theta = atan(y/x) / M_PI * 180;
    if (x < 0) return theta + 180;
    return theta;
}