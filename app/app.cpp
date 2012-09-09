#include <QtGui/QApplication>
#include "math/line.h"
#include <iostream>
#include "app/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Point um(1,2);
    Point dois(50,100);

    Line linha(um, dois);
    std::cout << um.x() << um.y() << std::endl;
    std::cout << dois.x() << dois.y() << std::endl;

    return a.exec();
}
