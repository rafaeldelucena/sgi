#include "view/window.h"
#include <math.h>

#define PI 3.14159265

Window::Window(const Point &min, const Point &max) : WC_min(min), WC_max(max)
{

    double windowcenter_x = (WC_max.x() - WC_min.x())/2;
    double windowcenter_y = (WC_max.y() - WC_min.y())/2;

    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = -windowcenter_x;
    m[7] = -windowcenter_y;
    m[8] = 1.0;

    WC_min = WC_min.transform(m);
    WC_max = WC_max.transform(m);

    _vup = (WC_max.y() - WC_min.y())/2;
    _u = 0;
}

Window::~Window(void)
{
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
    double windowcenter_x = (WC_max.x() - WC_min.x())/2;
    double windowcenter_y = (WC_max.y() - WC_min.y())/2;

    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = -windowcenter_x;
    m[7] = -windowcenter_y;
    m[8] = 1.0;

    WC_min = WC_min.transform(m);
    WC_max = WC_max.transform(m);

    // TODO
    _vup = cos(angle * PI/180.0);
    _u = sin(angle * PI/180.0);

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m2[9] = { 0 };
    m[0] = cos(angle * PI/180.0);
    m[1] = -sin(angle * PI/180.0);
    m[3] = sin(angle * PI/180.0);
    m[4] = cos(angle * PI/180.0);
    m[8] = 1.0;

    WC_min = WC_min.transform(m2);
    WC_max = WC_max.transform(m2);
}

double Window::u(void)
{
    return _u;
}

double Window::vup(void)
{
    return _vup;
}

const Point& Window::WCmax(void) const
{
    return WC_max;
}

const Point& Window::WCmin(void) const
{
    return WC_min;
}

void Window::right(double value)
{
    WC_min.x(WC_min.x() + value);
    WC_max.x(WC_max.x() + value);
}

void Window::left(double value)
{
    WC_min.x(WC_min.x() - value);
    WC_max.x(WC_max.x() - value);
}

void Window::up(double value)
{
    WC_min.y(WC_min.y() + value);
    WC_max.y(WC_max.y() + value);
}

void Window::down(double value)
{
    WC_min.y(WC_min.y() - value);
    WC_max.y(WC_max.y() - value);
}

void Window::reset(void)
{
    WC_min.x(-250);
    WC_min.y(-250);
    WC_max.x(250);
    WC_max.y(250);
}

void Window::reset(double minx, double miny, double maxx, double maxy)
{
    WC_min.x(minx);
    WC_min.y(miny);
    WC_max.x(maxx);
    WC_max.y(maxy);
}

#include <iostream>
void Window::enlarge(double value)
{
   std::cout << "max point original is " << WC_max.x() << "," << WC_max.y() << std::endl;
   std::cout << "min point original is " << WC_min.x() << "," << WC_min.y() << std::endl;
   std::cout << "center point original is" << ((WC_max.x() + WC_min.x())/2.0) << "," << ((WC_max.y() + WC_min.y())/2.0) << std::endl;

   double WC_minXfactor = (WC_max.x() - WC_min.x()) * (value / 100) / 2;
   double WC_minYfactor = (WC_max.y() - WC_min.y()) * (value / 100) / 2;
   double WC_maxXfactor = (WC_max.x() - WC_min.x()) * (value / 100) / 2;
   double WC_maxYfactor = (WC_max.y() - WC_min.y()) * (value / 100) / 2;

   WC_min.x(WC_min.x() - WC_minXfactor);
   WC_min.y(WC_min.y() - WC_minYfactor);
   WC_max.x(WC_max.x() + WC_maxXfactor);
   WC_max.y(WC_max.y() + WC_maxYfactor);


   std::cout << "max point now is " << WC_max.x() << "," << WC_max.y() << std::endl;
   std::cout << "min point now is " << WC_min.x() << "," << WC_min.y() << std::endl;
   std::cout << "center point now is " << ((WC_max.x() + WC_min.x())/2.0) << "," << ((WC_max.y() + WC_min.y())/2.0) << std::endl;

}

void Window::decrease(double value)
{
   std::cout << "max point original is " << WC_max.x() << "," << WC_max.y() << std::endl;
   std::cout << "min point original is " << WC_min.x() << "," << WC_min.y() << std::endl;
   std::cout << "center point original is" << ((WC_max.x() + WC_min.x())/2.0) << "," << ((WC_max.y() + WC_min.y())/2.0) << std::endl;


   double WC_minXfactor = (WC_max.x() - WC_min.x()) * (value / 100) / 2;
   double WC_minYfactor = (WC_max.y() - WC_min.y()) * (value / 100) / 2;
   double WC_maxXfactor = (WC_max.x() - WC_min.x()) * (value / 100) / 2;
   double WC_maxYfactor = (WC_max.y() - WC_min.y()) * (value / 100) / 2;

   WC_min.x(WC_min.x() + WC_minXfactor);
   WC_min.y(WC_min.y() + WC_minYfactor);
   WC_max.x(WC_max.x() - WC_maxXfactor);
   WC_max.y(WC_max.y() - WC_maxYfactor);


   std::cout << "max point now is " << WC_max.x() << "," << WC_max.y() << std::endl;
   std::cout << "min point now is " << WC_min.x() << "," << WC_min.y() << std::endl;
   std::cout << "center point now is " << ((WC_max.x() + WC_min.x())/2.0) << "," << ((WC_max.y() + WC_min.y())/2.0) << std::endl;

}
