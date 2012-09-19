#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "view/window.h"
#include "view/displayfile.h"
#include "app/formas.h"
#include "forms/canhamo.h"

class ViewPort
{
public:
    ViewPort(Canhamo* canvas, Window* window, DisplayFile* displayfile);
    ~ViewPort(void);

    Point transform(Point &point);
    void draw();

private:
    Point vMin;
    Point vMax;
    Window *window;
    DisplayFile *displayFile;
    Canhamo *canvas;
};

#endif // VIEWPORT_H
