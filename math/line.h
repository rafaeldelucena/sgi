#ifndef LINE_H
#define LINE_H

#include "math/point.h"

class Line
{
public:
    Line(const Point&, const Point&);
private:
    Point begin;
    Point end;
};

#endif // LINE_H
