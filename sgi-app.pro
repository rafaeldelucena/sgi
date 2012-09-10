QT  += core gui

TARGET = sgi-app
TEMPLATE = app

SOURCES += app/app.cpp\
    app/mainwindow.cpp \
    app/controller.cpp \
    view/displayfile.cpp \
    view/viewport.cpp \
    view/window.cpp \
    math/point.cpp \
    math/line.cpp \
    math/polygon.cpp

HEADERS  += app/mainwindow.h \
    app/controller.h \
    app/controller.h \
    view/displayfile.h \
    view/viewport.h \
    view/window.h \
    math/point.h \
    math/line.h \
    math/polygon.h \
    view/displayfile.h \
    view/viewport.h \
    view/window.h

FORMS    += forms/mainwindow.ui
