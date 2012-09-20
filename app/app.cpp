#include <QtGui/QApplication>
#include <QGraphicsScene>

#include "app/mainwindow.h"

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   MainWindow *mainWindow = new MainWindow();
   mainWindow->show();

   a.exec();
   delete mainWindow;
   return 0;
}
