#include "math/point.h"
#include <sstream>

Point::Point(double x, double y, double z)
    : Object(POINT), coordX(x), coordY(y), coordZ(z)
{
}

Point::Point(const Point &point)
    : Object(POINT), coordX(point.x()), coordY(point.y()), coordZ(point.z())
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

double Point::z(void) const
{
    return coordZ;
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "Point(" << x() << ","<< y() << "," << z() << ")";
    return s.str();
}
