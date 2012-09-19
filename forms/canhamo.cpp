#include "canhamo.h"
#include <QPainter>

Canhamo::Canhamo(QWidget* obj): QWidget(obj) {}

void Canhamo::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.drawLine(1,1,50,50);
}
