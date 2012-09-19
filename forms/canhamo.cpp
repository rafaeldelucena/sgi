#include "canhamo.h"
#include <QPainter>

Canhamo::Canhamo(QWidget* obj): QWidget(obj) {

     b_inicial_x = -1000;
     b_inicial_y = -1000;
     b_final_x = -2000;
     b_final_y = -2000;

}

void Canhamo::paintEvent(QPaintEvent*) {
    
    //TESTE
      QPainter p(this);
      p.setPen(QPen(Qt::red, 2));
      
     
      
      p.drawLine(b_inicial_x,b_inicial_y, b_final_x, b_final_y);
   
    
    
}

void Canhamo::desenharLinha(int inicial_x, int inicial_y, int final_x, int final_y){

     b_inicial_x = inicial_x;
     b_inicial_y = inicial_y;
     b_final_x = final_x;
     b_final_y = final_y;
     this->update();
}
