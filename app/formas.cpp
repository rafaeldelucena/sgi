#include "app/formas.h"

Object::Object(Shape type)
{
    shape = type;
}

Object::~Object(void)
{
}

Shape Object::type(void) const
{
    return shape;
}

std::string Object::toString(void) const
{
    std::stringstream s;
    s << "Object[type=" << type() << ";pontos=";
    unsigned int i;
    for (i=0; i < pointsCount(); i++)
    {
        s << "(" << point(i).x() << "," << point(i).y() << "," << point(i).z() << "),";
    }
    s << "]" << std::endl;

    return s.str();
}
void Object::addPoint(const Point &point)
{
    points.push_back(point);
}

int Object::pointsCount(void) const
{
    return points.size();
}

Point Object::point(int index) const
{
    return points[index];
}

Point::Point(double x, double y, double z) : coordX(x), coordY(y), coordZ(z)
{
}

Point::Point(const Point &point) : coordX(point.x()), coordY(point.y()), coordZ(point.z())
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

void Point::x(double x)
{
    this->coordX = x;
}

void Point::y(double y)
{
    this->coordY = y;
}
void Point::z(double z)
{
    this->coordZ = z;
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "Point(" << x() << ","<< y() << "," << z() << ")" << std::endl;
    return s.str();
}
