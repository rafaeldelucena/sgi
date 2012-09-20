#include "canhamo.h"

Canhamo::Canhamo(QWidget* obj): QWidget(obj)
{
}

#include <iostream>
void Canhamo::paintEvent(QPaintEvent*) {

    painter.begin(this);

    painter.setPen(QPen(Qt::blue, 1));
    painter.fillRect(0, 0, width(), height(), Qt::white);

    unsigned int i;
    for (i=0; i < canvasLines.size(); i++) {
        painter.drawLine(canvasLines[i].v[0], canvasLines[i].v[1], canvasLines[i].v[2], canvasLines[i].v[3]);
    }

    painter.end();
    canvasLines.clear();
}

void Canhamo::drawLine(const Point &begin, const Point &end){

    Line line = { { begin.x(), begin.y(), end.x(), end.y() } }; 
    canvasLines.push_back(line);
}

void Canhamo::refresh()
{
    this->update();
}
