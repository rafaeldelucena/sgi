#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "math/point.h"

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

#endif // POLYGON_H
