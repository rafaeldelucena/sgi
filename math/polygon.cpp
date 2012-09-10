#include "math/polygon.h"

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
    points.clear();
}

void Polygon::addPoint(const Point &point)
{
    points.push_back(point);
}

int Polygon::numberOfPoints(void) const
{
    return points.size();
}

const Points& Polygon::listOfPoints(void) const
{
    return this->points;
}
