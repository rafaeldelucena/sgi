#include "view/viewport.h"

ViewPort::ViewPort(Canhamo *cv, DisplayFile *d)
: vMin(0.0, 0.0, 0.0), vMax(500.0, 500.0, 0.0)
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
    window->left(value);
    draw();
}

void ViewPort::right(double value)
{
    window->right(value);
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
    unsigned int i;
    for (i=0; i < displayFile->objectsSize(); i++)
    {
        Object* obj = displayFile->getObjectAt(i);
        obj->updateSNC(window->u(), window->vup());
    }
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

Point ViewPort::transform(const Point &wCoord)
{
    double vCoordX = ( (wCoord.sncX() - window->sncmin_x()) / (window->sncmax_x() - window->sncmin_x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 - ( (wCoord.sncY() - window->sncmin_y()) / (window->sncmax_y() - window->sncmin_y()))) * (vMax.y() - vMin.y());

    return Point(vCoordX, vCoordY);
}

void ViewPort::draw()
{
    canvas->clear();

    unsigned int i;
    for (i=0; i < displayFile->objectsSize(); i++)
    {
        Object* obj = displayFile->getObjectAt(i);
        if (obj->type() == POINT) {
            // desenha um X com centro no ponto

            Point vPoint = transform(obj->point(0));
            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() - 1.0), Point(vPoint.x() + 1.0, vPoint.y() + 1.0),
                             obj->color.r, obj->color.g, obj->color.b);
            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() + 1.0), Point(vPoint.x() + 1.0, vPoint.y() - 1.0),
                             obj->color.r, obj->color.g, obj->color.b);
        } else {
            unsigned int i;
            Point startPoint(obj->point(0));
            Point endPoint(obj->point(obj->pointsCount() - 1));
            for (i=0; i < obj->pointsCount() - 1; i++) {
                startPoint = obj->point(i);
                startPoint = transform(startPoint);
                endPoint = obj->point(i+1);
                endPoint = transform(endPoint);
                canvas->drawLine(startPoint, endPoint, obj->color.r, obj->color.g, obj->color.b);
            }
            if (obj->type() == POLYGON) {
                startPoint = obj->point(0);
                startPoint = transform(startPoint);
                canvas->drawLine(endPoint, startPoint, obj->color.r, obj->color.g, obj->color.b);
            }
        }
    }
    displayFile->update();
    canvas->refresh();
}
