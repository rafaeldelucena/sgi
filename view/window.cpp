#include "window.h"

Window::Window(const Point &min, const Point &max) : minPoint(min), maxPoint(max)
{
}

Window::~Window(void)
{
}

const Point& Window::max(void) const
{
    return maxPoint;
}

const Point& Window::min(void) const
{
    return minPoint;
}
