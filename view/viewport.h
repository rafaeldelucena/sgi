#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "view/window.h"
#include "app/formas.h"
#include "forms/canhamo.h"


class ViewPort
{
public:
    ViewPort(Canhamo* canvas, Window* window);
    ~ViewPort(void);
    
    Point transform(Point &point);
    Line transform(Line *line);
    Polygon transform(Polygon *polygon);

    void draw(Point *point);
    void draw(Line *line);
    void draw(Polygon *polygon);
    void draw(ObjectsPtr&);
    void draw(Object *object);
    void redrawAll();

private:
    Point vMin;
    Point vMax;
    Window *window;
    Canhamo *canvas;
};

#endif // VIEWPORT_H
