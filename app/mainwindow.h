#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QStringListModel>
#include <QPushButton>

#include "math/polygon.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QGraphicsView* canvas();
    
private slots:
    void onPushPointSaveButton(void);
    void onPushLineSaveButton(void);
    void onPushPolygonSaveButton(void);
    void onPushPolygonAddButton(void);

private:
    Ui::MainWindow *ui;
    Points points;
    QStringListModel *pointsList;
    QStringList pointNames;
};

#endif // MAINWINDOW_H
