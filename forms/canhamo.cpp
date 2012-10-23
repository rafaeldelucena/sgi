#include "canhamo.h"

Canhamo::Canhamo(QWidget* obj): QWidget(obj)
{
    offset = 25;
}

void Canhamo::paintEvent(QPaintEvent*) {
    painter.begin(this);
    painter.fillRect(0, 0, width(), height(), Qt::white);
    painter.drawLine(25,475,25,25);
    painter.drawLine(25,25,475,25);
    painter.drawLine(475,25,475,475);
    painter.drawLine(475,475,25,475);
    Lines::iterator iter;
    for (iter = canvasLines.begin(); iter != canvasLines.end(); iter++) {
        QPen pen(QColor(iter->c[0], iter->c[1], iter->c[2]), 1);
        painter.setPen(pen);   	
        painter.drawLine(iter->v[0] + offset, iter->v[1] + offset, iter->v[2] + offset, iter->v[3] + offset);
    }

    Polygons::iterator it;
    for(it = canvasPolygons.begin(); it != canvasPolygons.end(); it++) {
        QPen pen(QColor(it->c[0], it->c[1], it->c[2]), 1);
        QBrush brush;
        if (it->filled) {
            brush = QBrush(QColor(it->c[0], it->c[1], it->c[2]));
            painter.setBrush(brush);
            painter.setPen(pen);
            painter.drawPolygon(it->points, Qt::WindingFill);
        } else {
            painter.setPen(pen);
            painter.setBrush(brush);
            painter.drawPolygon(it->points);
        }
    } 
    painter.end();
}

void Canhamo::drawLine(const Point &begin, const Point &end, int r, int g, int b){

    CanvasLine line = { { begin.x(), begin.y(), end.x(), end.y() }, { r, g, b } };
    canvasLines.push_back(line);
}

void Canhamo::drawPolygon(const std::vector<Point> &pontos, bool filled, int r, int g, int b)
{
    QVector<QPointF> pts;
    for (unsigned int i=0; i < pontos.size(); i++)
    {
        pts << QPointF(pontos[i].x() + offset, pontos[i].y() + offset);
    }
    
    CanvasPolygon polygon;
    polygon.points = pts;
    polygon.c[0]= r;
    polygon.c[1]= g;
    polygon.c[2]= b;
    polygon.filled = filled;
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
