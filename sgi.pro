QT  += core gui

TARGET = sgi
TEMPLATE = app

CONFIG += qt debug

SOURCES += app/app.cpp\
    app/mainwindow.cpp \
    app/formas.cpp \
    view/displayfile.cpp \
    view/viewport.cpp \
    view/window.cpp

HEADERS  +=\
    app/mainwindow.h \
    app/formas.h \
    view/displayfile.h \
    view/viewport.h \
    view/window.h

FORMS    += forms/mainwindow.ui

