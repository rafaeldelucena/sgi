#include "view/window.h"
#include <math.h>

#define PI 3.14159265

Window::Window(const Point &min, const Point &max) 
  : windowMin(min), windowMax(max)
{
    _vup = 0;
}

Window::~Window(void)
{
}

Point Window::scale(void)
{
    Point _scale(windowMax.x() - windowMin.x(), windowMax.y() - windowMin.y());
    return _scale;
}

Point Window::center(void)
{
    Point _windowCenter((windowMax.x() - windowMin.x())/2, (windowMax.y() - windowMin.y())/2);
        return _windowCenter;
}

double Window::sncmin_x(void)
{
    return -1;
}

double Window::sncmin_y(void)
{
    return -1;
}

double Window::sncmax_x(void)
{
    return 1;
}

double Window::sncmax_y(void)
{
    return 1;
}

void Window::rotate(double angle)
{

    // transladar window center
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = -center().x();
    m[7] = -center().y();
    m[8] = 1.0;

    windowCenterSNC = center().transform(m);

    _vup = _vup + angle;

    // rotacionar window center
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m2[9] = { 0 };
    m2[0] = cos(-_vup * PI/180.0);
    m2[1] = -sin(-_vup * PI/180.0);
    m2[3] = sin(-_vup * PI/180.0);
    m2[4] = cos(-_vup * PI/180.0);
    m2[8] = 1.0;

    windowCenterSNC = windowCenterSNC.transform(m2);
}

double Window::vup(void)
{
    return _vup;
}

const Point& Window::WCmax(void) const
{
    return windowMax;
}

const Point& Window::WCmin(void) const
{
    return windowMin;
}

void Window::right(double value)
{
    windowMin.x(windowMin.x() + value);
    windowMax.x(windowMax.x() + value);
}

void Window::left(double value)
{
    windowMin.x(windowMin.x() - value);
    windowMax.x(windowMax.x() - value);
}

void Window::up(double value)
{
    windowMin.y(windowMin.y() + value);
    windowMax.y(windowMax.y() + value);
}

void Window::down(double value)
{
    windowMin.y(windowMin.y() - value);
    windowMax.y(windowMax.y() - value);
}

void Window::reset(void)
{
    windowMin.x(-250);
    windowMin.y(-250);
    windowMax.x(250);
    windowMax.y(250);
}

void Window::reset(double minx, double miny, double maxx, double maxy)
{
    windowMin.x(minx);
    windowMin.y(miny);
    windowMax.x(maxx);
    windowMax.y(maxy);
}

#include <iostream>
void Window::enlarge(double value)
{
   std::cout << "max point original is " << windowMax.x() << "," << windowMax.y() << std::endl;
   std::cout << "min point original is " << windowMin.x() << "," << windowMin.y() << std::endl;
   std::cout << "center point original is" << ((windowMax.x() + windowMin.x())/2.0) << "," << ((windowMax.y() + windowMin.y())/2.0) << std::endl;

   double windowMinXfactor = (windowMax.x() - windowMin.x()) * (value / 100) / 2;
   double windowMinYfactor = (windowMax.y() - windowMin.y()) * (value / 100) / 2;
   double windowMaxXfactor = (windowMax.x() - windowMin.x()) * (value / 100) / 2;
   double windowMaxYfactor = (windowMax.y() - windowMin.y()) * (value / 100) / 2;

   windowMin.x(windowMin.x() - windowMinXfactor);
   windowMin.y(windowMin.y() - windowMinYfactor);
   windowMax.x(windowMax.x() + windowMaxXfactor);
   windowMax.y(windowMax.y() + windowMaxYfactor);

   std::cout << "max point now is " << windowMax.x() << "," << windowMax.y() << std::endl;
   std::cout << "min point now is " << windowMin.x() << "," << windowMin.y() << std::endl;
   std::cout << "center point now is " << ((windowMax.x() + windowMin.x())/2.0) << "," << ((windowMax.y() + windowMin.y())/2.0) << std::endl;

}

void Window::decrease(double value)
{
   std::cout << "max point original is " << windowMax.x() << "," << windowMax.y() << std::endl;
   std::cout << "min point original is " << windowMin.x() << "," << windowMin.y() << std::endl;
   std::cout << "center point original is" << ((windowMax.x() + windowMin.x())/2.0) << "," << ((windowMax.y() + windowMin.y())/2.0) << std::endl;


   double windowMinXfactor = (windowMax.x() - windowMin.x()) * (value / 100) / 2;
   double windowMinYfactor = (windowMax.y() - windowMin.y()) * (value / 100) / 2;
   double windowMaxXfactor = (windowMax.x() - windowMin.x()) * (value / 100) / 2;
   double windowMaxYfactor = (windowMax.y() - windowMin.y()) * (value / 100) / 2;

   windowMin.x(windowMin.x() + windowMinXfactor);
   windowMin.y(windowMin.y() + windowMinYfactor);
   windowMax.x(windowMax.x() - windowMaxXfactor);
   windowMax.y(windowMax.y() - windowMaxYfactor);

   std::cout << "max point now is " << windowMax.x() << "," << windowMax.y() << std::endl;
   std::cout << "min point now is " << windowMin.x() << "," << windowMin.y() << std::endl;
   std::cout << "center point now is " << ((windowMax.x() + windowMin.x())/2.0) << "," << ((windowMax.y() + windowMin.y())/2.0) << std::endl;

}
