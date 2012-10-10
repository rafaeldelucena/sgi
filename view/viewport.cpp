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
    double vCoordX = ( (point.sncX() - window->sncmin_x()) / (window->sncmax_x() - window->sncmin_x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 - ( (point.sncY() - window->sncmin_y()) / (window->sncmax_y() - window->sncmin_y()))) * (vMax.y() - vMin.y());

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

        if (obj->type() == POINT) {
            // desenha um X com centro no ponto

            Point p = obj->point(0);
            p.updateSNC(window->center(), window->vup(), window->scale());

            Point vPoint = transform(p);

            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() - 1.0), Point(vPoint.x() + 1.0, vPoint.y() + 1.0),
                    obj->color.r, obj->color.g, obj->color.b);
            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() + 1.0), Point(vPoint.x() + 1.0, vPoint.y() - 1.0),
                    obj->color.r, obj->color.g, obj->color.b);
        } else {
            if (obj->type() == LINE) {
                Point startPoint(obj->point(0));
                Point endPoint(obj->point(obj->pointsCount() - 1));
                startPoint.updateSNC(window->center(), window->vup(), window->scale());
                startPoint = transform(startPoint);

                endPoint.updateSNC(window->center(), window->vup(), window->scale());
                endPoint = transform(endPoint);

                canvas->drawLine(startPoint, endPoint, obj->color.r, obj->color.g, obj->color.b);
            } else {
                std::vector<Point> pontos;
                for (unsigned int i = 0; i < obj->pointsCount(); i++) {
                    Point polyPoint = obj->point(i);
                    polyPoint.updateSNC(window->center(), window->vup(), window->scale());
                    polyPoint = transform(polyPoint);
                    pontos.push_back(polyPoint);
                    canvas->drawPolygon(pontos, obj->isFilled(), obj->color.r, obj->color.g, obj->color.b);

                }

            }
        }
    }
    displayFile->update();
    canvas->refresh();
}
