#include "app/formas.h"

Line::Line(const Point &a, const Point &b)
    : Object(LINE), beginPoint(a), endPoint(b)
{
}

Point & Line::begin(void)
{
    return beginPoint;
}

Point & Line::end(void)
{
    return endPoint;
}

std::string Line::toString(void) const
{
    std::stringstream s;
    s << "Line[("<< beginPoint.x() << "," << beginPoint.y() << "," << beginPoint.z() <<")("
        << endPoint.x() << "," << endPoint.y() << "," << endPoint.z() << ")]";
    return s.str();
}

Object::Object(Shape type, QString name)
    : objectName(name)
{
    shape = type;
}

Object::~Object(void)
{
    objectName.clear();
}

Shape Object::type(void) const
{
    return shape;
}

QString Object::name(void) const
{
    return objectName;
}

void Object::name(QString anotherName)
{
    objectName = anotherName;
}

std::string Object::toString(void) const
{
    std::string str = "Unknown Object";
    return str;
}

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
    s << "Point(" << x() << ","<< y() << "," << z() << ")";
    return s.str();
}

Polygon::Polygon()
    : Object(POLYGON)
{
}

Polygon::~Polygon()
{
    polygonPoints.clear();
}

void Polygon::addPoint(const Point &point)
{
    polygonPoints.push_back(point);
}

Points & Polygon::points(void)
{
    return polygonPoints;
}

std::string Polygon::toString(void) const
{
    std::stringstream s;
    s << "Polygon[";
    unsigned int i;
    for (i=0; i < polygonPoints.size(); i++)
    {
        s << "(" << polygonPoints[i].x() << "," << polygonPoints[i].y() << "," << polygonPoints[i].z() << ")";
    }
    s << "]";

    return s.str();
}
