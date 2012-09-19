#include "canhamo.h"

Canhamo::Canhamo(QWidget* obj): QWidget(obj) {

     b_inicial_x = 1000;
     b_inicial_y = 1000;
     b_final_x = 2000;
     b_final_y = 2000;
}

void Canhamo::paintEvent(QPaintEvent*) {

    painter.begin(this);

    painter.setPen(QPen(Qt::red, 2));

    painter.drawLine(b_inicial_x,b_inicial_y, b_final_x, b_final_y);
    painter.end();
}

void Canhamo::drawLine(Point begin, Point end){

     b_inicial_x = begin.x();
     b_inicial_y = begin.y();
     b_final_x = end.x();
     b_final_y = end.y();
     this->update();
}
