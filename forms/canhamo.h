#ifndef CANHAMO_H
#define CANHAMO_H

#include <vector>
#include <QWidget>
#include <QPainter>
#include <QPolygonF>

#include "view/formas.h"

typedef struct
{
    double v[4];
    int c[3];
} Line;

typedef struct
{
	QVector<QPointF> points;
        int c[3];
        bool filled;
} CanvasPolygon;

typedef std::vector<Line> Lines;
typedef std::vector<CanvasPolygon> Polygons;

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
    void drawLine(const Point &begin, const Point &end, int r, int g, int b);
    void drawPolygon(const std::vector<Point> &points, bool filled, int r, int g, int b);
    void refresh();
    void clear();

private:
    QPainter painter;
    Lines canvasLines;
    Polygons canvasPolygons;
    bool polygonFilled;
    int offset; 
};

#endif // CANHAMO_H
