#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>
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
    void enlarge(double value);
    void decrease(double value);
    void centralize(void);

private:
    Point minPoint;
    Point maxPoint;
};

#endif // WINDOW_H
