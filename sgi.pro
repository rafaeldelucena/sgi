QT  += core gui

TARGET = sgi
TEMPLATE = app

CONFIG += qt debug

SOURCES += app/app.cpp\
    app/mainwindow.cpp \
    view/formas.cpp \
    view/displayfile.cpp \
    view/viewport.cpp \
    view/window.cpp \
    forms/canhamo.cpp

HEADERS  +=\
    app/mainwindow.h \
    view/formas.h \
    view/displayfile.h \
    view/viewport.h \
    view/window.h \
    forms/canhamo.h

FORMS    += forms/mainwindow.ui

