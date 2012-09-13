#ifndef POINT_H
#define POINT_H

#include "math/object.h"

class Point : public Object
{
public:
    Point(double x, double y, double z);
    Point(const Point& point);

    double x(void) const;
    double y(void) const;
    double z(void) const;

    std::string toString(void) const;

private:
    double coordX, coordY, coordZ;
};

#endif // POINT_H
