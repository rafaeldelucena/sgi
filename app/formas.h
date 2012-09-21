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

    Point rotate(double a);
    Point scale(const Point& vector);
    Point translate(const Point& displacement);

    std::string toString(void) const;

private:
    double coordX, coordY, coordZ;

    Point transform(double matrix[9]);
};

typedef std::vector<Point> Points;

class Object {
public:
    Object(Shape type);
    virtual ~Object(void);
    Shape type(void) const;
    unsigned int pointsCount(void) const;
    Point point(int index) const;
    void addPoint(const Point &point);

    Object* rotate(double a);
    Object* scale(const Point& vector);
    Object* translate(const Point& displacement);

    virtual std::string toString(void) const;

private:
    Shape shape;
    int color;
    Points points;
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
