#include <QtGui/QApplication>
#include <QGraphicsScene>
#include "app/controller.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   Controller control;

   Point point(100,100);

   control.addObject(point);

   Line line1(Point(0,0), Point(0,50));
   control.addObject(line1);

   Line line2(Point(0,0), Point(0,-50));
   control.addObject(line2);

   Line line3(Point(0,0), Point(50,0));
   control.addObject(line3);

   Line line4(Point(0,0), Point(-50,0));
   control.addObject(line4);

   Line line5(Point(0,0), Point(-50,-50));
   control.addObject(line5);

   Line line6(Point(0,0), Point(50,50));
   control.addObject(line6);

   Polygon polygon;

   polygon.addPoint(Point(-50.0,-50.0));
   polygon.addPoint(Point(-50.0,50.0));
   polygon.addPoint(Point(50.0,50.0));
   polygon.addPoint(Point(50.0,-50.0));
   polygon.addPoint(Point(-50.0,-50.0));

   control.addObject(polygon);

   return a.exec();
}
