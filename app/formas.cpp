#include "app/formas.h"

Line::Line(const Point &a, const Point &b, QString name)
    : Object(LINE, name), beginPoint(a), endPoint(b)
{
}

Point Line::begin(void) const
{
    return beginPoint;
}

Point Line::end(void) const
{
    return endPoint;
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

Polygon::Polygon(QString name)
    : Object(POLYGON, name)
{
}

Polygon::~Polygon()
{
    points.clear();
}

void Polygon::addPoint(const Point &point)
{
    points.push_back(point);
}

int Polygon::numberOfPoints(void) const
{
    return points.size();
}

const Points& Polygon::listOfPoints(void) const
{
    return this->points;
}
