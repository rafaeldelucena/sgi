#ifndef FORMAS_H
#define FORMAS_H

#include <QString>
#include <vector>

#include <sstream>

enum Shape { POINT, LINE, POLYGON };

class Object {
public:
    Object(Shape type, QString name = "Object");
    virtual ~Object(void);
    Shape type(void) const;
    QString name(void) const;
    void name(QString anotherName);

    virtual std::string toString(void) const;

private:
    Shape shape;
    QString objectName;
};

class Point : public Object
{
public:
    Point(double x, double y, double z);
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

class Line: public Object
{
public:
    Line(const Point &, const Point &);
    Point & begin(void);
    Point & end(void);

    std::string toString(void) const;
private:
    Point beginPoint;
    Point endPoint;
};

typedef std::vector<Point> Points;
typedef std::vector<Object*> ObjectsPtr;

class Polygon : public Object
{
public:
    Polygon();
    ~Polygon(void);
    void addPoint(const Point& point);
    Points &points(void); 

    std::string toString(void) const;
private:
    Points polygonPoints;
};

#endif // FORMAS_H
