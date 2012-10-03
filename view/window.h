#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>
#include "app/formas.h"

class Window
{
public:
    Window(const Point &WCmin, const Point &WCmax);
    ~Window();
    const Point &WCmin(void) const;
    const Point &WCmax(void) const;
    double u(void);
    double vup(void);

    double sncmax_x(void);
    double sncmax_y(void);
    double sncmin_x(void);
    double sncmin_y(void);

    void right(double value);
    void left(double value);
    void up(double value);
    void down(double value);
    void enlarge(double value);
    void decrease(double value);
    void reset(void);
    void reset(double minx, double miny, double maxx, double maxy);
    void rotate(double angle);

private:
    Point WC_min;
    Point WC_max;
    double _vup;
    double _u;
};

#endif // WINDOW_H
