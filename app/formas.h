#ifndef FORMAS_H
#define FORMAS_H

#include <QString>
#include <vector>

#include <sstream>

enum Shape { POINT, LINE, POLYGON };

class Point
{
public:
    Point(double x, double y, double z = 1.0);
    Point(const Point& point);

    double x(void) const;
    double y(void) const;
    double z(void) const;

    void x(double);
    void y(double);
    void z(double);

    std::string toString(void) const;

private:
    double coordX, coordY, coordZ;
};

typedef std::vector<Point> Points;

class Object {
public:
    Object(Shape type);
    virtual ~Object(void);
    Shape type(void) const;
    int pointsCount(void) const;
    Point point(int index) const;
    void addPoint(const Point &point);

    virtual std::string toString(void) const;

private:
    Shape shape;
    Points points;
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
