#include "canhamo.h"

Canhamo::Canhamo(QWidget* obj): QWidget(obj)
{
    offset = 25;
}

#include <iostream>
void Canhamo::paintEvent(QPaintEvent*) {
    painter.begin(this);

    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.drawLine(25,475,25,25);
    painter.drawLine(25,25,475,25);
    painter.drawLine(475,25,475,475);
    painter.drawLine(475,475,25,475);
    unsigned int i;
    for (i=0; i < canvasLines.size(); i++) {
	QPen pen(QColor(canvasLines[i].c[0], canvasLines[i].c[1], canvasLines[i].c[2]), 1);
	painter.setPen(pen);   	
        painter.drawLine(canvasLines[i].v[0] + offset, canvasLines[i].v[1] + offset, canvasLines[i].v[2] + offset, canvasLines[i].v[3] + offset);
    }
    for(i=0; i < canvasPolygons.size(); i++) {
	QPen pen(QColor(canvasPolygons[i].c[0], canvasPolygons[i].c[1], canvasPolygons[i].c[2]), 1);
	QBrush brush;
	if (canvasPolygons[i].filled) {
		brush = QBrush(QColor(canvasPolygons[i].c[0], canvasPolygons[i].c[1], canvasPolygons[i].c[2]));
		painter.setBrush(brush);
		painter.setPen(pen);
    		painter.drawPolygon(canvasPolygons[i].points, Qt::WindingFill);
        } else {
        	painter.setPen(pen);
		painter.setBrush(brush);
    		painter.drawPolygon(canvasPolygons[i].points);
	}
    } 
    painter.end();
}

void Canhamo::drawLine(const Point &begin, const Point &end, int r, int g, int b){

    Line line = { { begin.x(), begin.y(), end.x(), end.y() }, { r, g, b } };
    canvasLines.push_back(line);
}
void Canhamo::drawPolygon(std::vector<Point> & pontos, bool filled, int r, int g, int b)
{
	CanvasPolygon polygon;
        polygon.c[0] = r;
        polygon.c[1] = g;
        polygon.c[2] = b;

        polygon.filled = filled;
	for (unsigned i = 0; i < pontos.size(); i++)
	{
		polygon.points << QPointF(pontos[i].x() + offset, pontos[i].y() + offset);
	}
	if (!polygon.points.empty()) {
	    canvasPolygons.push_back(polygon);
        }
}

void Canhamo::refresh()
{
    this->update();
}

void Canhamo::clear()
{
    canvasLines.clear();
    canvasPolygons.clear();
}
