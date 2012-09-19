#include <QWidget>

class Canhamo : public QWidget {
    Q_OBJECT
public:
    Canhamo(QWidget* obj=0);
    void paintEvent(QPaintEvent*);
};