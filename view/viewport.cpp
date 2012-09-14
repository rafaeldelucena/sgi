#include "view/viewport.h"

ViewPort::ViewPort(QGraphicsView* cv, Window* window)
: vMin(-90.0, -90.0, 0.0), vMax(90.0, 90.0, 0.0),
  wMin(window->min()), wMax(window->max())
{
    canvas = cv;
    scene = new QGraphicsScene(vMin.x(), vMin.y(), 200, 200, canvas);
}

ViewPort::~ViewPort()
{
    delete scene;
}

Point ViewPort::transform(Point & wCoord)
{
    double vCoordX = ( (wCoord.x() - wMin.x())
                 / (wMax.x() - wMin.x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 -
                 ( (wCoord.y() - wMin.y()) / (wMax.y() - wMin.y()))
                 * (vMax.y() - vMin.y()) );

    return Point(vCoordX, vCoordY);
}

Line ViewPort::transform(Line *line)
{
    Line vLine(transform(line->begin()), transform(line->end()));
    return vLine;
}

Polygon ViewPort::transform(Polygon *polygon)
{
    unsigned int i;
    Polygon poly;
    for (i=0; i < polygon->points().size(); i++) {
        poly.addPoint(transform(polygon->points()[i]));
    }
    return poly;
}

#include <iostream>
void ViewPort::draw(Point *point)
{
    Point vPoint = transform(*point);
    scene->addLine(vPoint.x(), vPoint.y(), vPoint.x(), vPoint.y());
}

void ViewPort::draw(Line *line)
{
    Line vLine = transform(line);
    scene->addLine(vLine.begin().x(), vLine.begin().y(), vLine.end().x(), vLine.end().y());
}

void ViewPort::draw(Polygon *polygon)
{
    Polygon vPolygon = transform(polygon);
    unsigned int i;
    for (i=0; i < polygon->points().size() - 1; i++) {
        scene->addLine(vPolygon.points()[i].x(), vPolygon.points()[i].y(),
                vPolygon.points()[i+1].x(), vPolygon.points()[i+1].y());
    }
    scene->addLine(vPolygon.points().back().x(), vPolygon.points().back().y(),
            vPolygon.points().front().x(), vPolygon.points().front().y()); 
}

void ViewPort::draw(Object* object)
{
    switch(object->type()) {
        case (POINT) :
            draw((Point*)object);
            break;
        case (LINE) :
            draw((Line*)object);
            break;
        case (POLYGON) :
            draw((Polygon*)object);
            break;
    }
}

void ViewPort::draw(ObjectsPtr& objects)
{
    scene->clear();
    unsigned int i;
    for (i=0; i < objects.size(); i++)
    {
        draw(objects[i]);
    }
    canvas->setScene(scene);
}
