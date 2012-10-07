#ifndef WINDOW_H
#define WINDOW_H

#include <math.h>

#include "view/formas.h"

class Window
{
public:
    Window(const Point &WCmin, const Point &WCmax);
    ~Window();
    const Point &WCmin(void) const;
    const Point &WCmax(void) const;
    Point center(void);
    Point centerSNC(void);
    Point scale(void);
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

    void updateSNC(void);

private:
    Point windowMin;
    Point windowMax;
    Point windowCenterSNC;
    double _vup;
};

#endif // WINDOW_H
