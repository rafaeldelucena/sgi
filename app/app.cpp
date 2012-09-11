#include <QtGui/QApplication>
#include "app/controller.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   Controller *control = Controller::instance();
   
   a.exec();

   delete control;
   return 0;
}
