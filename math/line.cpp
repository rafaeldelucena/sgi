#include "math/line.h"

Line::Line(const Point &a, const Point &b)
    : Object(LINE), beginPoint(a), endPoint(b)
{
    nominate("Line");
}

Point Line::begin(void) const
{
    return beginPoint;
}

Point Line::end(void) const
{
    return endPoint;
}
