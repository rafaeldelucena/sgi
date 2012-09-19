#ifndef CANHAMO_H
#define CANHAMO_H

#include <QWidget>
#include "app/formas.h"

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
    void drawLine(Point begin, Point End);
    
private:
    int b_inicial_x;
    int b_inicial_y;
    int b_final_x;
    int b_final_y;
};

#endif // CANHAMO_H
