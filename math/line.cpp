#include "math/line.h"

Line::Line(const Point &a, const Point &b, QString name)
    : Object(LINE, name), beginPoint(a), endPoint(b)
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
