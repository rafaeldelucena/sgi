#include "app/controller.h"

Controller::Controller(void)
{
    mainWindow = new MainWindow();
    Point wMax(500.0, 500.0);
    Point wMin(0.0, 0.0);
    Point vpMax(450.0, 450.0);
    Point vpMin(1.0, 1.0);
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

void Controller::addObject(const Point &point)
{
    Point newPoint(Point(point.x(), point.y()));
    viewPort->addPoint(newPoint);
    displayFile->insertObject(&newPoint);
}

void Controller::addObject(const Line &line)
{
    Line newLine(line.begin(), line.end());
    viewPort->addLine(newLine);
    displayFile->insertObject(&newLine);
}

void Controller::addObject(const Polygon &polygon)
{
    Polygon newPolygon(polygon);
    viewPort->addPolygon(newPolygon);
    displayFile->insertObject(&newPolygon);
}
