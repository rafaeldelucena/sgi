#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view/displayfile.h"
#include "view/window.h"
#include "view/viewport.h"
#include "app/mainwindow.h"

class Controller
{
public:
    Controller(void);
    ~Controller(void);
    void addObject(const Point& point);
    void addObject(const Line& line);
    void addObject(const Polygon& polygon);
private:
    DisplayFile *displayFile;
    Window *window;
    ViewPort *viewPort;
    MainWindow *mainWindow;
};

#endif // CONTROLLER_H
