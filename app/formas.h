#ifndef FORMAS_H
#define FORMAS_H

#include <QString>
#include <vector>

#include <sstream>

enum Shape { POINT, LINE, POLYGON };

class Point
{
public:
    Point(double x = 0.0, double y =0.0, double z = 0.0);
    Point(const Point& point);

    double x(void) const;
    double y(void) const;
    double z(void) const;

    void x(double);
    void y(double);
    void z(double);

    Point transform(double matrix[9]);
    std::string toString(void) const;
    std::string toObj(void) const;

private:
    double coordX, coordY, coordZ;
};

typedef std::vector<Point*> Points;

typedef struct
{
    int r;
    int g;
    int b;
} Color;

class Object {
public:
    Object(Shape type, int r = 0, int g = 0, int b = 0);
    ~Object(void);
    Shape type(void) const;
    unsigned int pointsCount(void) const;
    Point point(int index);
    void addPoint(double x, double y, double z);
    Point getCenterPoint(void);

    void rotateOrigin(double angle);
    void rotateCenter(double angle);
    void rotatePoint(double angle,const Point& p);
    void scale(const Point& vector);
    void translate(const Point& displacement);
    void clearTransformations(void);

    Color color;

private:
    Shape shape;
    Points points;
    double transformationMatrix[9];
    void updateTransform(double m[9]);
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
