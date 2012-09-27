#ifndef FORMAS_H
#define FORMAS_H

#include <QString>
#include <vector>

#include <sstream>

enum Shape { POINT, LINE, POLYGON };

typedef struct
{
    double v[9];
} Matrix;

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

    void transform(const Matrix &matrix);
    Point transform2(const Matrix &matrix);

    std::string toString(void) const;

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
    Point* point(int index) const;
    void addPoint(double x, double y, double z);
    Point getCenterPoint(void);

    void rotateOrigin(double angle);
    void rotateCenter(double angle);
    void rotatePoint(double angle,const Point& p);
    void scale(const Point& vector);
    void translate(const Point& displacement);
    void transform(void);
    void clearTransformations(void);

    Matrix transformations();

    std::string toString(void) const;

    Color color;

private:
    Shape shape;
    Points points;
    Matrix transformationMatrix;
    void updateTransform(const Matrix &);
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
