#ifndef WINDOW_H
#define WINDOW_H

#include "app/formas.h"

class Window
{
public:
    Window(const Point &min, const Point &max);
    ~Window();
    const Point &max(void) const;
    const Point &min(void) const;

    void right(double value);
    void left(double value);
    void up(double value);
    void down(double value);
    void shrink(double value);
    void stretch(double value);

private:
    Point minPoint;
    Point maxPoint;
};

#endif // WINDOW_H
