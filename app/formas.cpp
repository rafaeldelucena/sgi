#include "app/formas.h"
#include <math.h>

#define PI 3.14159265

Object::Object(Shape type)
{
    shape = type;
    color.r = 0;
    color.g = 0;
    color.b = 0;
}

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
        s << "(" << point(i).x() << "," << point(i).y() << "," << point(i).z() << "),";
    }
    s << "]" << std::endl;

    return s.str();
}
void Object::addPoint(const Point &point)
{
    points.push_back(point);
}

unsigned int Object::pointsCount(void) const
{
    return points.size();
}

Point Object::point(int index) const
{
    return points[index];
}

Object* Object::rotate(double a)
{
    Object* new_obj = new Object(type()); // add color
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        new_obj->addPoint(point(i).rotate(a));
    }
    return new_obj;
}

Object* Object::scale(const Point& vector)
{
    Object* new_obj = new Object(type()); // add color
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        new_obj->addPoint(point(i).scale(vector));
    }
    return new_obj;
}

Object* Object::translate(const Point& displacement)
{
    Object* new_obj = new Object(type()); // add color
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        new_obj->addPoint(point(i).translate(displacement));
    }
    return new_obj;
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

Point Point::rotate(double a)
{
    double m[9];
    m[1] = cos(a * PI/180);
    m[2] = -sin(a * PI/180);
    m[3] = 0.0;
    m[4] = sin(a * PI/180);
    m[5] = cos(a * PI/180);
    m[6] = 0.0;
    m[7] = 0.0;
    m[8] = 1.0;
    return transform(m);
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
}

Point Point::scale(const Point& vector)
{
    double m[9];
    m[0] = vector.x();
    m[1] = 0.0;
    m[2] = 0.0;
    m[3] = 0.0;
    m[4] = vector.y();
    m[5] = 0.0;
    m[6] = 0.0;
    m[7] = 0.0;
    m[8] = 1.0;
    return transform(m);
    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
}

Point Point::translate(const Point& displacement)
{
    double m[9];
    m[0] = 1.0;
    m[1] = 0.0;
    m[2] = 0.0;
    m[3] = 0.0;
    m[4] = 1.0;
    m[5] = 0.0;
    m[6] = displacement.x();
    m[7] = displacement.y();
    m[8] = 1.0;
    return transform(m);
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
}

Point Point::transform(double matrix[9])
{
    //return [x y 1]*[matrix]
    double new_x = (x() * matrix[0]) + (y() * matrix[3]) + matrix[6];
    double new_y = (x() * matrix[1]) + (y() * matrix[4]) + matrix[7];
    double new_z = (x() * matrix[2]) + (y() * matrix[5]) + matrix[8];
    Point p = Point(new_x, new_y, new_z);
    return p;
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "Point(" << x() << ","<< y() << "," << z() << ")" << std::endl;
    return s.str();
}
