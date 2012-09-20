#include "view/viewport.h"

ViewPort::ViewPort(Canhamo *cv, Window *w, DisplayFile *d)
: vMin(0.0, 0.0, 0.0), vMax(440.0, 340.0, 0.0)
{
    canvas = cv;
    window = w;
    displayFile = d;
}

ViewPort::~ViewPort()
{
}

Point ViewPort::transform(Point & wCoord)
{
    double vCoordX = ( (wCoord.x() - window->min().x()) / (window->max().x() - window->min().x()) ) * (vMax.x() - vMin.x());
    double vCoordY = (1.0 - ( (wCoord.y() - window->min().y()) / (window->max().y() - window->min().y()))) * (vMax.y() - vMin.y());

    return Point(vCoordX, vCoordY);
}

void ViewPort::draw()
{
    unsigned int i;
    for (i=0; i < displayFile->objectsSize(); i++)
    {
        Object* obj = displayFile->getObjectAt(i);
        if (obj->type() == POINT) {

            Point vPoint = obj->point(0);
            vPoint = transform(vPoint);
            // desenha um X com centro no ponto
            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() - 1.0), Point(vPoint.x() + 1.0, vPoint.y() + 1.0));
            canvas->drawLine(Point(vPoint.x() -1.0, vPoint.y() + 1.0), Point(vPoint.x() + 1.0, vPoint.y() - 1.0));


        } else {
            unsigned int i;
            Point startPoint = obj->point(0);
            Point endPoint = obj->point(obj->pointsCount() - 1);
            for (i=0; i < obj->pointsCount() - 1; i++) {
                startPoint = obj->point(i);
                startPoint = transform(startPoint);
                endPoint = obj->point(i+1);
                endPoint = transform(endPoint);
                canvas->drawLine(startPoint, endPoint);
            }
            if (obj->type() == POLYGON) {
                startPoint = obj->point(0);
                startPoint = transform(startPoint);
                canvas->drawLine(endPoint, startPoint);
                displayFile->update();
            }
        }
    }
    canvas->refresh();
}
