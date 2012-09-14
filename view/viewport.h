#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include "view/window.h"
#include "app/formas.h"

class ViewPort
{
public:
    ViewPort(QGraphicsView* canvas, Window* window);
    ~ViewPort(void);
    
    Point transform(Point &point);
    Line transform(Line *line);
    Polygon transform(Polygon *polygon);

    void draw(Point *point);
    void draw(Line *line);
    void draw(Polygon *polygon);
    void draw(ObjectsPtr&);
    void draw(Object *object);

private:
    Point vMin;
    Point vMax;
    Point wMin;
    Point wMax;
    QGraphicsView *canvas;
    QGraphicsScene *scene;
};

#endif // VIEWPORT_H
