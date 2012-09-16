#include "view/window.h"

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

void Window::right(double value)
{
    minPoint.x(minPoint.x() + value); 
    maxPoint.x(maxPoint.x() + value);
}

void Window::left(double value)
{
    minPoint.x(minPoint.x() - value);
    maxPoint.x(maxPoint.x() - value);
}

void Window::up(double value)
{
    minPoint.y(minPoint.y() + value);
    maxPoint.y(maxPoint.y() + value);
}

void Window::down(double value)
{
    minPoint.y(minPoint.y() - value);
    maxPoint.y(maxPoint.y() - value);
}

void Window::stretch(double value)
{
   minPoint.x(minPoint.x() - value);
   minPoint.y(minPoint.y() - value);

   maxPoint.x(maxPoint.x() + value);
   maxPoint.y(maxPoint.y() + value);
}

void Window::shrink(double value)
{
   minPoint.x(minPoint.x() + value);
   minPoint.y(minPoint.y() + value);

   maxPoint.x(maxPoint.x() - value);
   maxPoint.y(maxPoint.y() - value);
}
