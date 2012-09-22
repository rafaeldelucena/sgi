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

    void rotate(double a);
    void scale(const Point& vector);
    void translate(const Point& displacement);

    std::string toString(void) const;

private:
    double coordX, coordY, coordZ;

    void transform(double matrix[9]);
};

typedef std::vector<Point> Points;

typedef struct
{
    int r;
    int g;
    int b;
} Color;

class Object {
public:
    Object(Shape type);
    Object(Shape type, int r, int g, int b);
    ~Object(void);
    Shape type(void) const;
    unsigned int pointsCount(void) const;
    Point point(int index) const;
    void addPoint(const Point &point);

    void rotate_origin(double angle);
    void rotate_center(double angle);
    void rotate_point(double angle,const Point& p);
    void scale(const Point& vector);
    void translate(const Point& displacement);

    std::string toString(void) const;

    Color color;

private:
    Shape shape;
    Points points;
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
