#include "math/line.h"

Line::Line(const Point &a, const Point &b) : beginPoint(a), endPoint(b)
{
}

Point Line::begin(void) const
{
    return beginPoint;
}

Point Line::end(void) const
{
    return endPoint;
}
