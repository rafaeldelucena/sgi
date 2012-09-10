#ifndef LINE_H
#define LINE_H

#include "math/point.h"

class Line
{
public:
    Line(const Point&, const Point&);
    Point begin(void) const;
    Point end(void) const;
private:
    Point beginPoint;
    Point endPoint;
};

#endif // LINE_H
