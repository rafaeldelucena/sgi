#include <QtGui/QApplication>
#include <QGraphicsScene>
#include "app/controller.h"

#include <iostream>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   Controller control;
   
   return a.exec();
}
