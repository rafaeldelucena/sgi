QT  += core gui

TARGET = sgi-app
TEMPLATE = app

SOURCES += app/app.cpp\
    app/mainwindow.cpp \
    math/point.cpp \
    math/line.cpp \
    math/polygon.cpp

HEADERS  += app/mainwindow.h \
    math/point.h \
    math/line.h \
    math/polygon.h

FORMS    += forms/mainwindow.ui
