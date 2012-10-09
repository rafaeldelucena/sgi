#include "canhamo.h"

Canhamo::Canhamo(QWidget* obj): QWidget(obj)
{
}

void Canhamo::paintEvent(QPaintEvent*) {

    painter.begin(this);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.drawLine(25,475,25,25);
    painter.drawLine(25,25,475,25);
    painter.drawLine(475,25,475,475);
    painter.drawLine(475,475,25,475);
	int offset = 25;
    unsigned int i;
    for (i=0; i < canvasLines.size(); i++) {
        painter.setPen(QPen(QColor(canvasLines[i].c[0], canvasLines[i].c[1], canvasLines[i].c[2]), 1));
        painter.drawLine(canvasLines[i].v[0] + offset, canvasLines[i].v[1] + offset, canvasLines[i].v[2] + offset, canvasLines[i].v[3] + offset);
    }
    painter.end();
}

void Canhamo::drawLine(const Point &begin, const Point &end, int r, int g, int b){

    Line line = { { begin.x(), begin.y(), end.x(), end.y() }, { r, g, b } };
    canvasLines.push_back(line);
}

void Canhamo::refresh()
{
    this->update();
}

void Canhamo::clear()
{
    canvasLines.clear();
}
