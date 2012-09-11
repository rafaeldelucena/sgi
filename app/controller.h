#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view/displayfile.h"
#include "view/window.h"
#include "view/viewport.h"
#include "app/mainwindow.h"

class Controller
{
public:
    ~Controller(void);
    static Controller* instance(void);
    void addObject(const Point& point);
    void addObject(const Line& line);
    void addObject(const Polygon& polygon);
private:
    Controller(void);

    DisplayFile *displayFile;
    Window *window;
    ViewPort *viewPort;
    MainWindow *mainWindow;
    static Controller *controller;
};

#endif // CONTROLLER_H
