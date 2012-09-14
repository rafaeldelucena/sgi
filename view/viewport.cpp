#include "view/viewport.h"

ViewPort::ViewPort(QGraphicsView* cv, Window* window)
: minVpPoint(-90.0, -90.0, 0.0), maxVpPoint(90.0, 90.0, 0.0),
  minWPoint(window->min()), maxWPoint(window->max())
{
    canvas = cv;
    scene = new QGraphicsScene(260, 40, 450, 340, canvas);
    draw();
}

ViewPort::~ViewPort()
{
    delete scene;
}

Point ViewPort::transform(const Point &coordinate)
{
    double x = ( (coordinate.x() - minWPoint.x())
                 / (maxWPoint.x() - minWPoint.x()) ) * (maxVpPoint.x() - minVpPoint.y() );
    double y = (1.0 -
                 ( (coordinate.y() - minWPoint.y()) / (maxWPoint.y() - minWPoint.y()))
                 * (maxVpPoint.y() - minVpPoint.y())
               );
    double z = 0.0;
    Point point = Point(x, y, z);

    return point;
}

Line ViewPort::transform(const Line &lineCoordinate)
{
    Point begin = transform(lineCoordinate.begin());
    Point end = transform(lineCoordinate.end());
    Line line = Line(begin, end);

    return line;
}

Polygon ViewPort::transform(const Polygon &polygonCoordinates)
{
    Polygon polygon;
    int i;
    for (i=0; i < polygonCoordinates.numberOfPoints(); i++) {
        Point point = transform(polygonCoordinates.listOfPoints()[i]);
        polygon.addPoint(point);
    }
    return polygon;
}

void ViewPort::addPoint(const Point &point)
{
    Point newPoint = transform(point);
    scene->addLine(newPoint.x(), newPoint.y(), newPoint.x(), newPoint.y());
    draw();
}

void ViewPort::addLine(const Line &line)
{
    Line newLine = transform(line);
    Point begin = newLine.begin();
    Point end = newLine.end();
    scene->addLine(begin.x(), begin.y(), end.x(), end.y());
    draw();
}

void ViewPort::addPolygon(const Polygon &polygon)
{
    Polygon newPolygon(transform(polygon));
    int i;
    for (i=0; i < newPolygon.numberOfPoints() - 1; i++) {
        Line newLine(newPolygon.listOfPoints()[i], newPolygon.listOfPoints()[i+1]);
        addLine(newLine);
    }
    Line line(newPolygon.listOfPoints().back(), newPolygon.listOfPoints().front());
    addLine(line);
    draw();
}

void ViewPort::draw(void)
{
    canvas->setScene(scene);
}
