#include "math/point.h"

Point::Point(double x, double y)
    : Object(POINT), coordX(x), coordY(y)
{
}

Point::Point(const Point &point)
    : Object(POINT), coordX(point.x()), coordY(point.y())
{
}

double Point::x(void) const
{
    return coordX;
}

double Point::y(void) const
{
    return coordY;
}
