#include <QWidget>

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
    void drawLine(QPaintEvent*);

private:
    void desenharLinha(int inicial_x, int inicial_y, int final_x, int final_y);
};