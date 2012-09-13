#ifndef FORMAS_H
#define FORMAS_H

#include <QString>
#include <vector>

#include <sstream>

enum Shape { POINT, LINE, POLYGON };

class Object {
public:
    Object(Shape type, QString name);
    ~Object(void);
    Shape type(void) const;
    QString name(void) const;

private:
    Shape shape;
    QString objectName;
};

class Point : public Object
{
public:
    Point(double x, double y, double z, QString name = "Point");
    Point(const Point& point, QString name = "Point");

    double x(void) const;
    double y(void) const;
    double z(void) const;

    std::string toString(void) const;

private:
    double coordX, coordY, coordZ;
};

class Line: public Object
{
public:
    Line(const Point &, const Point &, QString name = "Line");
    Point begin(void) const;
    Point end(void) const;
private:
    Point beginPoint;
    Point endPoint;
};

typedef std::vector<Point> Points;

class Polygon : public Object
{
public:
    Polygon(QString name = "Polygon");
    ~Polygon(void);
    void addPoint(const Point& point);
    int numberOfPoints(void) const;
    const Points& listOfPoints(void) const;
private:
    Points points;
};

#endif // FORMAS_H
