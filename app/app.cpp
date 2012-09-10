#include <QtGui/QApplication>
#include "app/controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller control;
    Line line1(Point(0,0), Point(10,300));
    Line line2(Point(50,0), Point(122,300));

    control.addObject(line1);
    control.addObject(line2);
    return a.exec();
}
