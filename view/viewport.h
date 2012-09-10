#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include "math/polygon.h"
#include "math/line.h"

class ViewPort
{
public:
    ViewPort(QGraphicsView* canvas, const Point &vpMin, const Point &vpMax, const Point &wMin, const Point &wMax);
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
