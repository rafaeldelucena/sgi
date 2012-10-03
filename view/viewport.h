#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "view/window.h"
#include "view/displayfile.h"
#include "app/formas.h"
#include "forms/canhamo.h"

class ViewPort
{
public:
    ViewPort(Canhamo* canvas, DisplayFile* displayfile);
    ~ViewPort(void);

    Point transform(const Point &wCoord);
    Point minWindowPoint(void);
    Point maxWindowPoint(void);
    void draw(void);
    void right(double value);
    void left(double value);
    void up(double value);
    void down(double value);
    void zoomIn(double value);
    void zoomOut(double value);
    void reset(void);
    void reset(double minx, double miny, double maxx, double maxy);
    void rotate(double angle);

private:
    Point vMin;
    Point vMax;
    Window *window;
    DisplayFile *displayFile;
    Canhamo *canvas;
};

#endif // VIEWPORT_H
