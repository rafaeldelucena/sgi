#include "math/point.h"
#include <sstream>

Point::Point(double x, double y, double z, QString name)
    : Object(POINT, name), coordX(x), coordY(y), coordZ(z)
{
}

Point::Point(const Point &point, QString name)
    : Object(POINT, name), coordX(point.x()), coordY(point.y()), coordZ(point.z())
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
