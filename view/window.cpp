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

void Window::reset()
{
    minPoint.x(-250);
    minPoint.y(-250);
    maxPoint.x(250);
    maxPoint.y(250);
}

void Window::reset(double minx, double miny, double maxx, double maxy)
{
    minPoint.x(minx);
    minPoint.y(miny);
    maxPoint.x(maxx);
    maxPoint.y(maxy);
}

#include <iostream>
void Window::enlarge(double value)
{
   std::cout << "max point original is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point original is " << minPoint.x() << "," << minPoint.y() << std::endl;

   double factor = (maxPoint.x() - minPoint.x()) * (value / 100) / 2;
   minPoint.x(minPoint.x() - factor);
   factor = (maxPoint.y() - minPoint.y()) * (value / 100) / 2;
   minPoint.y(minPoint.y() - factor);

   factor = (maxPoint.x() - minPoint.x()) * (value / 100) / 2;
   maxPoint.x(maxPoint.x() + factor);
   factor = (maxPoint.y() - minPoint.y()) * (value / 100) / 2;
   maxPoint.y(maxPoint.y() + factor);

   std::cout << "max point now is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point now is " << minPoint.x() << "," << minPoint.y() << std::endl;
}

void Window::decrease(double value)
{
   std::cout << "max point original is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point original is " << minPoint.x() << "," << minPoint.y() << std::endl;

   double factor = (maxPoint.x() - minPoint.x()) * (value / 100) / 2;
   minPoint.x(minPoint.x() + factor);
   factor = (maxPoint.y() - minPoint.y()) * (value / 100) / 2;
   minPoint.y(minPoint.y() + factor);

   factor = (maxPoint.x() - minPoint.x()) * (value / 100) / 2;
   maxPoint.x(maxPoint.x() - factor);
   factor = (maxPoint.y() - minPoint.y()) * (value / 100) / 2;
   maxPoint.y(maxPoint.y() - factor);

   std::cout << "max point now is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point now is " << minPoint.x() << "," << minPoint.y() << std::endl;
}
