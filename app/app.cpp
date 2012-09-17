#include <QtGui/QApplication>
#include <QGraphicsScene>

#include "app/mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   MainWindow *mainWindow = new MainWindow();
   mainWindow->show();

   /*
   Point point1(10.0, 35.0);
   Line line1(Point(0,0), Point(10,50));
   Line line2(Point(50,0), Point(22,1));
   Polygon polygon;

   polygon.addPoint(Point(1.0,1.0));
   polygon.addPoint(Point(12.0,1.0));
   polygon.addPoint(Point(1.0,12.0));
   polygon.addPoint(Point(21.0,11.0));

   displayFile->insertObject(polygon);
   displayFile->insertObject(point1);
   displayFile->insertObject(point1);
   displayFile->insertObject(point1);
   displayFile->insertObject(point1);
   displayFile->insertObject(point1);
   displayFile->insertObject(line1);
   displayFile->insertObject(line2);
   */

   a.exec();
   delete mainWindow;
   return 0;
}
