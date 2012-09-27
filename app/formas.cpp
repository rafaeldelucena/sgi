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

void Object::updateTransform(const Matrix& matrix)
{
    //return [transformationMatrix]*[matrix]

    Matrix *t = &transformationMatrix;

    // linha 1
    double new_x1 = (t->v[0] * matrix.v[0]) + (t->v[1] * matrix.v[3]) + (t->v[2] * matrix.v[6]);
    double new_y1 = (t->v[0] * matrix.v[1]) + (t->v[1] * matrix.v[4]) + (t->v[2] * matrix.v[7]);
    double new_z1 = (t->v[0] * matrix.v[2]) + (t->v[1] * matrix.v[5]) + (t->v[2] * matrix.v[8]);

    // linha 2
    double new_x2 = (t->v[3] * matrix.v[0]) + (t->v[4] * matrix.v[3]) + (t->v[5] * matrix.v[6]);
    double new_y2 = (t->v[3] * matrix.v[1]) + (t->v[4] * matrix.v[4]) + (t->v[5] * matrix.v[7]);
    double new_z2 = (t->v[3] * matrix.v[2]) + (t->v[4] * matrix.v[5]) + (t->v[5] * matrix.v[8]);

    // linha 3
    double new_x3 = (t->v[6] * matrix.v[0]) + (t->v[7] * matrix.v[3]) + (t->v[8] * matrix.v[6]);
    double new_y3 = (t->v[6] * matrix.v[1]) + (t->v[7] * matrix.v[4]) + (t->v[8] * matrix.v[7]);
    double new_z3 = (t->v[6] * matrix.v[2]) + (t->v[7] * matrix.v[5]) + (t->v[8] * matrix.v[8]);

    t->v[0] = new_x1;
    t->v[1] = new_y1;
    t->v[2] = new_z1;
    t->v[3] = new_x2;
    t->v[4] = new_y2;
    t->v[5] = new_z2;
    t->v[6] = new_x3;
    t->v[7] = new_y3;
    t->v[8] = new_z3;
}

void Object::clearTransformations(void)
{
    transformationMatrix.v[0] = 1;
    transformationMatrix.v[1] = 0;
    transformationMatrix.v[2] = 0;
    transformationMatrix.v[3] = 0;
    transformationMatrix.v[4] = 1;
    transformationMatrix.v[5] = 0;
    transformationMatrix.v[6] = 0;
    transformationMatrix.v[7] = 0;
    transformationMatrix.v[8] = 1;
}

void Object::rotateOrigin(double a)
{
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    Matrix m;
    m.v[0] = cos(a * PI/180.0);
    m.v[1] = -sin(a * PI/180.0);
    m.v[3] = sin(a * PI/180.0);
    m.v[4] = cos(a * PI/180.0);
    m.v[8] = 1.0;
    updateTransform(m);
}

void Object::rotateCenter(double a)
{
    Point p = getCenterPoint();
    //p = p.transform2(this->transformationMatrix);
    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    Matrix m;
    m.v[0] = cos(a * PI/180.0);
    m.v[1] = -sin(a * PI/180.0);
    m.v[3] = sin(a * PI/180.0);
    m.v[4] = cos(a * PI/180.0);
    m.v[8] = 1.0;
    updateTransform(m);

    translate(Point(p.x(), p.y()));
}

void Object::rotatePoint(double a, const Point& p)
{

    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    Matrix m;
    m.v[0] = cos(a * PI/180.0);
    m.v[1] = -sin(a * PI/180.0);
    m.v[3] = sin(a * PI/180.0);
    m.v[4] = cos(a * PI/180.0);
    m.v[8] = 1.0;
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

    Matrix m;
    m.v[0] = vector.x();
    m.v[4] = vector.y();
    m.v[8] = 1;

    updateTransform(m);

    this->translate(Point(p.x(), p.y()));
}

void Object::translate(const Point& displacement)
{
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    Matrix m;
    m.v[0] = 1.0;
    m.v[4] = 1.0;
    m.v[6] = displacement.x();
    m.v[7] = displacement.y();
    m.v[8] = 1.0;
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

Matrix Object::transformations()
{
    return transformationMatrix;
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

void Point::transform(const Matrix &m)
{
    //return [x y 1]*[matrix]
    double new_x = (x() * m.v[0]) + (y() * m.v[3]) + m.v[6];
    double new_y = (x() * m.v[1]) + (y() * m.v[4]) + m.v[7];
    double new_z = (x() * m.v[2]) + (y() * m.v[5]) + m.v[8];
    x(new_x);
    y(new_y);
    z(new_z);
}

Point Point::transform2(const Matrix &m)
{
    //return [x y 1]*[matrix]
    double new_x = (x() * m.v[0]) + (y() * m.v[3]) + m.v[6];
    double new_y = (x() * m.v[1]) + (y() * m.v[4]) + m.v[7];
    double new_z = (x() * m.v[2]) + (y() * m.v[5]) + m.v[8];
    return Point(new_x, new_y, new_z);
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "v " << x() << " "<< y() << " " << z() << std::endl;
    return s.str();
}
