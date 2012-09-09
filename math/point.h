#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point(double x, double y);
    Point(const Point& point);

    double x(void) const;
    double y(void) const;
private:
    double coordX, coordY;
};

#endif // POINT_H
