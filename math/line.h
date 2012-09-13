#ifndef LINE_H
#define LINE_H

#include "math/point.h"

class Line: public Object
{
public:
    Line(const Point &, const Point &, QString name = "Line");
    Point begin(void) const;
    Point end(void) const;
private:
    Point beginPoint;
    Point endPoint;
};

#endif // LINE_H
