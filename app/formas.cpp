#include "app/formas.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265

Object::Object(Shape type, int r, int g, int b)
{
    shape = type;
    color.r = r;
    color.g = g;
    color.b = b;
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
        s << "(" << point(i)->x() << "," << point(i)->y() << "," << point(i)->z() << "),";
    }
    s << "]" << std::endl;

    return s.str();
}
void Object::addPoint(double x, double y, double z)
{
    Point* p = new Point(x, y, z);
    points.push_back(p);
}

unsigned int Object::pointsCount(void) const
{
    return points.size();
}

Point* Object::point(int index) const
{
    return points[index];
}

void Object::rotateOrigin(double a)
{
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->rotate(a);
    }
}

void Object::rotateCenter(double a)
{
    Point p = getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->rotate(a);
    }
    this->translate(Point(p.x(), p.y()));
}

void Object::rotatePoint(double a, const Point& p)
{
    this->translate(Point(-p.x(), -p.y()));
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->rotate(a);
    }
    this->translate(Point(p.x(), p.y()));
}

void Object::scale(const Point& vector)
{
    Point p = getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->scale(vector);
    }
    this->translate(Point(p.x(), p.y()));
}

void Object::translate(const Point& displacement)
{
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->translate(displacement);
    }
}

Point Object::getCenterPoint(void)
{
    double x = 0;
    double y = 0;
    unsigned int i;
    for (i=0; i < pointsCount(); i++)
    {
        x += point(i)->x();
        y += point(i)->y();
    }

    x = x/i;
    y = y/i;

    return Point(x, y);
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

void Point::rotate(double a)
{
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    transform(m);
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
}

void Point::scale(const Point& vector)
{
    double m[9] = { 0 };
    m[0] = vector.x();
    m[4] = vector.y();
    m[8] = 1;
    transform(m);
    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
}

void Point::translate(const Point& displacement)
{
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = displacement.x();
    m[7] = displacement.y();
    m[8] = 1.0;
    transform(m);
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
}

void Point::transform(double matrix[9])
{
    //return [x y 1]*[matrix]
    double new_x = (x() * matrix[0]) + (y() * matrix[3]) + matrix[6];
    double new_y = (x() * matrix[1]) + (y() * matrix[4]) + matrix[7];
    double new_z = (x() * matrix[2]) + (y() * matrix[5]) + matrix[8];
    x(new_x);
    y(new_y);
    z(new_z);
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "Point(" << x() << ","<< y() << "," << z() << ")" << std::endl;
    return s.str();
}
