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

#include <iostream>
void Window::enlarge(double value)
{
   double factor = (value / 100) / 2;
   std::cout << "enlarging by " << factor << std::endl;
   std::cout << "max point original is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point original is " << minPoint.x() << "," << minPoint.y() << std::endl;

   double abs_x_factor = fabs(maxPoint.x()) * factor;
   double abs_y_factor = fabs(maxPoint.y()) * factor;
   std::cout << "max_abs_factor is " << abs_x_factor << "," << abs_y_factor << std::endl;
    if (maxPoint.x() < 0) {
        maxPoint.x(maxPoint.x() - abs_x_factor );
    } else {
        maxPoint.x(maxPoint.x() + abs_x_factor );
    }
    if (maxPoint.y() < 0) {
        maxPoint.y(maxPoint.y() - abs_y_factor );
    } else {
        maxPoint.y(maxPoint.y() + abs_y_factor );
    }

    abs_x_factor = fabs(minPoint.x()) * factor;
    abs_y_factor = fabs(minPoint.y()) * factor;
    std::cout << "min_abs_factor is " << abs_x_factor << "," << abs_y_factor << std::endl;
    if (minPoint.x() < 0) {
        minPoint.x(minPoint.x() + abs_x_factor );
    } else {
        minPoint.x(minPoint.x() - abs_x_factor );
    }
    if (minPoint.y() < 0) {
        minPoint.y(minPoint.y() + abs_y_factor );
    } else {
        minPoint.y(minPoint.y() - abs_y_factor );
    }

   std::cout << "max point now is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
   std::cout << "min point now is " << minPoint.x() << "," << minPoint.y() << std::endl;
}

void Window::decrease(double value)
{
    double factor = (value / 100) / 2;
    std::cout << "decreasing by " << factor << std::endl;
    std::cout << "max point original is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
    std::cout << "min point original is " << minPoint.x() << "," << minPoint.y() << std::endl;

    double abs_x_factor = fabs(maxPoint.x()) * factor;
    double abs_y_factor = fabs(maxPoint.y()) * factor;
    std::cout << "max_abs_factor is " << abs_x_factor << "," << abs_y_factor << std::endl;
    if (maxPoint.x() < 0) {
        maxPoint.x(maxPoint.x() + abs_x_factor );
    } else {
        maxPoint.x(maxPoint.x() - abs_x_factor );
    }
    if (maxPoint.y() < 0) {
        maxPoint.y(maxPoint.y() + abs_y_factor );
    } else {
        maxPoint.y(maxPoint.y() - abs_y_factor );
    }

    abs_x_factor = fabs(minPoint.x()) * factor;
    abs_y_factor = fabs(minPoint.y()) * factor;
    std::cout << "min_abs_factor is " << abs_x_factor << "," << abs_y_factor << std::endl;
    if (minPoint.x() < 0) {
        minPoint.x(minPoint.x() - abs_x_factor );
    } else {
        minPoint.x(minPoint.x() + abs_x_factor );
    }
    if (minPoint.y() < 0) {
        minPoint.y(minPoint.y() - abs_y_factor );
    } else {
        minPoint.y(minPoint.y() + abs_y_factor );
    }

    std::cout << "max point now is " << maxPoint.x() << "," << maxPoint.y() << std::endl;
    std::cout << "min point now is " << minPoint.x() << "," << minPoint.y() << std::endl;
}
