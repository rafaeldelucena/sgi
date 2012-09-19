#ifndef CANHAMO_H
#define CANHAMO_H

#include <QWidget>

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
    void drawLine(QPaintEvent*);
    void desenharLinha(int inicial_x, int inicial_y, int final_x, int final_y);
    
private:
    int b_inicial_x;
    int b_inicial_y;
    int b_final_x;
    int b_final_y;
    
};

#endif // CANHAMO_H
