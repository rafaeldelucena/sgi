#include "app/controller.h"

Controller* Controller::controller = 0;

Controller::Controller(void)
{
    mainWindow = new MainWindow();
    Point wMax(100.0, 100.0, 0.0);
    Point wMin(0.0, 0.0, 0.0);
    Point vpMax(90.0, 90.0, 0.0);
    Point vpMin(1.0, 1.0, 0.0);
    displayFile = new DisplayFile();
    window = new Window(wMin, wMax);
    viewPort = new ViewPort(mainWindow->canvas(), window, vpMin, vpMax);

    mainWindow->show();
}

Controller::~Controller(void)
{
    delete mainWindow;
    delete viewPort;
    delete window;
    delete displayFile;
}

Controller* Controller::instance(void)
{
    if (!controller) {
        controller =  new Controller;
    }
    return controller;
}

void Controller::addObject(const Point &point)
{
    viewPort->addPoint(point);
    displayFile->insertObject(point);
}

void Controller::addObject(const Line &line)
{
    viewPort->addLine(line);
    displayFile->insertObject(line);
}

void Controller::addObject(const Polygon &polygon)
{
    viewPort->addPolygon(polygon);
    displayFile->insertObject(polygon);
}
