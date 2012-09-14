#include "view/viewport.h"

ViewPort::ViewPort(QGraphicsView* cv, Window* window)
: vMin(-90.0, -90.0, 0.0), vMax(90.0, 90.0, 0.0),
  wMin(window->min()), wMax(window->max())
{
    canvas = cv;
    scene = new QGraphicsScene(260, 40, 450, 340, canvas);
}

ViewPort::~ViewPort()
{
    delete scene;
}

void ViewPort::transform(Point & wCoord)
{
    double vCoordX = ( (wCoord.x() - wMin.x())
                 / (wMax.x() - wMin.x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 -
                 ( (wCoord.y() - wMin.y()) / (wMax.y() - wMin.y()))
                 * (vMax.y() - vMin.y()) );

    wCoord.x(vCoordX);
    wCoord.y(vCoordY);
}

void ViewPort::transform(Line *line)
{
    transform(line->begin());
    transform(line->end());
}

void ViewPort::transform(Polygon *polygon)
{
    unsigned int i;
    for (i=0; i < polygon->points().size(); i++) {
        transform(polygon->points()[i]);
    }
}

void ViewPort::draw(Point *point)
{
    scene->addLine(point->x(), point->y(), point->x(), point->y());
}

void ViewPort::draw(Line *line)
{
    scene->addLine(line->begin().x(), line->begin().y(), line->end().x(), line->end().y());
}

void ViewPort::draw(Polygon *polygon)
{
    unsigned int i;
    for (i=0; i < polygon->points().size() - 1; i++) {
        scene->addLine(polygon->points()[i].x(), polygon->points()[i].y(),
                polygon->points()[i+1].x(), polygon->points()[i+1].y());
    }
    scene->addLine(polygon->points().back().x(), polygon->points().back().y(),
            polygon->points().front().x(), polygon->points().front().y()); 
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
#include <iostream>
void ViewPort::draw(ObjectsPtr& objects)
{
    scene->clear();
    std::cout << "Numero de objetos :" << objects.size() << std::endl; 
    unsigned int i;
    for (i=0; i < objects.size(); i++)
    {
        draw(objects[i]);
    }
    std::cout << "Set scene" << std::endl;
    canvas->setScene(scene);
}
