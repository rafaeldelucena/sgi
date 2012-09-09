#include "math/point.h"

Point::Point(double x, double y) : coordX(x), coordY(y)
{
}

Point::Point(const Point& point) : coordX(point.x()), coordY(point.y())
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
