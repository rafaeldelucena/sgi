#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include "view/window.h"
#include "app/formas.h"

class ViewPort
{
public:
    ViewPort(QGraphicsView* canvas, Window* window);
    ~ViewPort();
    Point transform(const Point &coordinates);
    Line transform(const Line &lineCoordinates);
    Polygon transform(const Polygon &polygonCoordinates);

    void addLine(const Line &line);
    void addPoint(const Point &point);
    void addPolygon(const Polygon &polygon);

    void draw();
private:
    Point minVpPoint;
    Point maxVpPoint;
    Point minWPoint;
    Point maxWPoint;
    QGraphicsView *canvas;
    QGraphicsScene *scene;
};

#endif // VIEWPORT_H
