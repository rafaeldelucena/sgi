QT  += core gui

TARGET = sgi
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

CONFIG += qt debug

SOURCES += app/app.cpp\
    app/mainwindow.cpp \
    app/parser.cpp \
    view/formas.cpp \
    view/displayfile.cpp \
    view/viewport.cpp \
    view/window.cpp \
    forms/canhamo.cpp

HEADERS  +=\
    app/mainwindow.h \
    app/parser.h \
    view/formas.h \
    view/displayfile.h \
    view/viewport.h \
    view/window.h \
    forms/canhamo.h

FORMS    += forms/mainwindow.ui

