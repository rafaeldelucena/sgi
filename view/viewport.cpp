#include "view/viewport.h"

ViewPort::ViewPort(Canhamo *cv, DisplayFile *d)
: vMin(25.0, 25.0, 0.0), vMax(475.0, 475.0, 0.0)
{
    canvas = cv;
    displayFile = d;

    Point wMax(250.0, 250.0, 0.0);
    Point wMin(-250.0, -250.0, 0.0);
    window = new Window(wMin, wMax);
}

ViewPort::~ViewPort()
{
    delete window;
}

void ViewPort::up(double value)
{
    window->up(value);
    draw();
}

void ViewPort::down(double value)
{
    window->down(value);
    draw();
}

void ViewPort::left(double value)
{
    window->right(value);
    draw();
}

void ViewPort::right(double value)
{
    window->left(value);
    draw();
}

void ViewPort::reset(void)
{
    window->reset();
    draw();
}

void ViewPort::reset(double minx, double miny, double maxx, double maxy)
{
    window->reset(minx, miny, maxx, maxy);
    draw();
}

void ViewPort::zoomIn(double value)
{
    window->decrease(value);
    draw();
}

void ViewPort::zoomOut(double value)
{
    window->enlarge(value);
    draw();
}

void ViewPort::rotate(double angle)
{
    window->rotate(angle);
    draw();
}

Point ViewPort::minWindowPoint(void)
{
    return window->WCmin();
}

Point ViewPort::maxWindowPoint(void)
{
    return window->WCmax();
}

Point ViewPort::transform(const Point &point)
{
    double vCoordX = ( (point.x() - window->sncmin_x()) / (window->sncmax_x() - window->sncmin_x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 - ( (point.y() - window->sncmin_y()) / (window->sncmax_y() - window->sncmin_y()))) * (vMax.y() - vMin.y());

    Point p(vCoordX, vCoordY);

    return p;    
}

#include <iostream>

void ViewPort::draw(void)
{
    canvas->clear();

    window->updateSNC();

    unsigned int i;
    for (i=0; i < displayFile->objectsCount(); i++)
    {
        Object* obj = displayFile->getObjectAt(i);

        Object* clipped = obj->clip(window->sncmin_x(), window->sncmin_y(), window->sncmax_x(), window->sncmax_y(),
                                    window->center(), window->vup(), window->scale());

        if (!clipped) {
            continue;
        }

       // clipped->updateSNC(window->center(), window->vup(), window->scale());

        if (clipped->type() == POINT) {

            // desenha um X com centro no ponto
            Point p = clipped->point(0);

            Point vPoint = transform(p);

            canvas->drawLine(Point(vPoint.x() - 1.0, vPoint.y() - 1.0), Point(vPoint.x() + 1.0, vPoint.y() + 1.0),
                             obj->color.r, obj->color.g, obj->color.b);
            canvas->drawLine(Point(vPoint.x() - 1.0, vPoint.y() + 1.0), Point(vPoint.x() + 1.0, vPoint.y() - 1.0),
                             obj->color.r, obj->color.g, obj->color.b);

        } else if (clipped->type() == LINE) {

                Point startPoint = clipped->point(0);
//                startPoint.updateSNC(window->center(), window->vup(), window->scale());
                startPoint = transform(startPoint);

                Point endPoint = clipped->point(1);
//                endPoint.updateSNC(window->center(), window->vup(), window->scale());
                endPoint = transform(endPoint);

                canvas->drawLine(startPoint, endPoint, obj->color.r, obj->color.g, obj->color.b);

        } else if (clipped->type() == POLYGON) {

            Point startPoint;

            Point endPoint;

            for (unsigned int i = 0; i < clipped->pointsCount() - 1; i++) {

                startPoint = clipped->point(i);
//                startPoint.updateSNC(window->center(), window->vup(), window->scale());
                startPoint = transform(startPoint);

                endPoint = clipped->point(i+1);
//                endPoint.updateSNC(window->center(), window->vup(), window->scale());
                endPoint = transform(endPoint);

                canvas->drawLine(startPoint, endPoint, clipped->color.r, clipped->color.g, clipped->color.b);
            }

            startPoint = clipped->point(0);
//            startPoint.updateSNC(window->center(), window->vup(), window->scale());
            startPoint = transform(startPoint);

            canvas->drawLine(endPoint, startPoint, clipped->color.r, clipped->color.g, clipped->color.b);
        }
    }
    displayFile->update();
    canvas->refresh();
}
