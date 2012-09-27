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
    clearTransformations();
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

void Object::updateTransform(double matrix[9])
{
    //return [transformationMatrix]*[matrix]

    double *t = transformationMatrix;

    // linha 1
    double new_x1 = (t[0] * matrix[0]) + (t[1] * matrix[3]) + (t[2] * matrix[6]);
    double new_y1 = (t[0] * matrix[1]) + (t[1] * matrix[4]) + (t[2] * matrix[7]);
    double new_z1 = (t[0] * matrix[2]) + (t[1] * matrix[5]) + (t[2] * matrix[8]);

    // linha 2
    double new_x2 = (t[3] * matrix[0]) + (t[4] * matrix[3]) + (t[5] * matrix[6]);
    double new_y2 = (t[3] * matrix[1]) + (t[4] * matrix[4]) + (t[5] * matrix[7]);
    double new_z2 = (t[3] * matrix[2]) + (t[4] * matrix[5]) + (t[5] * matrix[8]);

    // linha 3
    double new_x3 = (t[6] * matrix[0]) + (t[7] * matrix[3]) + (t[8] * matrix[6]);
    double new_y3 = (t[6] * matrix[1]) + (t[7] * matrix[4]) + (t[8] * matrix[7]);
    double new_z3 = (t[6] * matrix[2]) + (t[7] * matrix[5]) + (t[8] * matrix[8]);

    t[0] = new_x1;
    t[1] = new_y1;
    t[2] = new_z1;
    t[3] = new_x2;
    t[4] = new_y2;
    t[5] = new_z2;
    t[6] = new_x3;
    t[7] = new_y3;
    t[8] = new_z3;
}

void Object::clearTransformations(void)
{
    transformationMatrix[0] = 1;
    transformationMatrix[1] = 0;
    transformationMatrix[2] = 0;
    transformationMatrix[3] = 0;
    transformationMatrix[4] = 1;
    transformationMatrix[5] = 0;
    transformationMatrix[6] = 0;
    transformationMatrix[7] = 0;
    transformationMatrix[8] = 1;
}

void Object::rotateOrigin(double a)
{
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);
}

void Object::rotateCenter(double a)
{
    Point p = getCenterPoint();
    p.transform(this->transformationMatrix);
    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);

    translate(Point(p.x(), p.y()));
}

void Object::rotatePoint(double a, const Point& p)
{

    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);

    translate(Point(p.x(), p.y()));
}

void Object::scale(const Point& vector)
{
    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
    Point p = getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));

    double m[9] = { 0 };
    m[0] = vector.x();
    m[4] = vector.y();
    m[8] = 1;

    updateTransform(m);

    this->translate(Point(p.x(), p.y()));
}

void Object::translate(const Point& displacement)
{
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = displacement.x();
    m[7] = displacement.y();
    m[8] = 1.0;
    updateTransform(m);
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

void Object::transform(void)
{
    for (unsigned int i=0; i < pointsCount(); i++)
    {
        point(i)->transform(transformationMatrix);
    }
    clearTransformations();
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
