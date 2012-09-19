#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include "view/window.h"
#include "view/displayfile.h"
#include "app/formas.h"

class ViewPort
{
public:
    ViewPort(QGraphicsView* canvas, Window* window, DisplayFile* displayfile);
    ~ViewPort(void);
    
    Point transform(Point &point);
    Line transform(Line *line);
    Polygon transform(Polygon *polygon);

    void draw();

private:
    Point vMin;
    Point vMax;
    Window *window;
    DisplayFile *displayFile;
    QGraphicsView *canvas;
    QGraphicsScene *scene;

    void draw(Point *point);
    void draw(Line *line);
    void draw(Polygon *polygon);
    void draw(Object *object);
};

#endif // VIEWPORT_H
