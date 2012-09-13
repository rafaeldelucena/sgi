#ifndef WINDOW_H
#define WINDOW_H

#include "app/formas.h"

class Window
{
public:
    Window(const Point &min, const Point &max);
    const Point &max(void) const;
    const Point &min(void) const;
    ~Window();
private:
    Point minPoint;
    Point maxPoint;
};

#endif // WINDOW_H
