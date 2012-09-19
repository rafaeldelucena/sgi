#include "canhamo.h"
#include <QPainter>

Canhamo::Canhamo(QWidget* obj): QWidget(obj) {}

void Canhamo::paintEvent(QPaintEvent*) {
    
    //TESTE
    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.drawLine(1,1,50,50);
    
}

void Canhamo::desenharLinha(int inicial_x, int inicial_y, int final_x, int final_y){

    QPainter p(this);
    p.setPen(QPen(Qt::black, 1));
    p.drawLine(inicial_x, inicial_y, final_x, final_y);

}
