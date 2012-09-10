#ifndef WINDOW_H
#define WINDOW_H

#include "math/point.h"

class Window
{
public:
    Window(const Point &min, const Point &max);
    ~Window();
private:
    Point minPoint;
    Point maxPoint;
};

#endif // WINDOW_H
