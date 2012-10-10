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

    double sncX(void) const;
    double sncY(void) const;
    double sncZ(void) const;

    void x(double);
    void y(double);
    void z(double);

    void updateSNC(const Point& windowCenter, double vup, const Point& scale);

    Point transform(double matrix[9]);
    std::string toString(void) const;
    std::string toObj(void) const;

private:
    double wcX, wcY, wcZ;
    double snc_X, snc_Y, snc_Z;
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

    int regionCode(double x, double y, double xmin, double ymin, double xmax, double ymax);

    Point point(int index);
    Point getCenterPoint(void);

    void addPoint(double x, double y, double z);

    void rotateOrigin(double angle);
    void rotateCenter(double angle);
    void rotatePoint(double angle,const Point& p);
    void scale(const Point& vector);
    void translate(const Point& displacement);
    void clearTransformations(void);
    bool isFilled(void);
    void fill(bool);

    void updateSNC(const Point& windowCenter, double vup, const Point& scale);

    Object* clip(double wmin_x, double wmin_y, double wmax_x, double wmax_y,
                 const Point& windowCenter, double vup, const Point& scale);

    Color color;

private:
    bool filled;
    Shape shape;
    Points points;
    double transformationMatrix[9];
    void updateTransform(double m[9]);
};
typedef std::vector<Object*> Objects;

#endif // FORMAS_H
