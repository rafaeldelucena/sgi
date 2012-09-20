#ifndef CANHAMO_H
#define CANHAMO_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include "app/formas.h"

typedef struct
{
    int v[4];
} Line;

typedef std::vector<Line> Lines;

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
    void drawLine(const Point &begin, const Point &end);
    void refresh();
    
private:
    QPainter painter;
    Lines canvasLines;
};

#endif // CANHAMO_H
