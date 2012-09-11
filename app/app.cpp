#include <QtGui/QApplication>
#include <QGraphicsScene>
#include "app/controller.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   Controller control;
   Line line1(Point(0,0), Point(10,50));
   Line line2(Point(50,0), Point(22,1));
   Polygon polygon;

   polygon.addPoint(Point(1.0,1.0));
   polygon.addPoint(Point(12.0,1.0));
   polygon.addPoint(Point(1.0,12.0));
   polygon.addPoint(Point(21.0,11.0));

   control.addObject(polygon);
   control.addObject(line1);
   control.addObject(line2);
   return a.exec();
}
