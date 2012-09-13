#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QStringListModel>
#include <QPushButton>

#include "math/line.h"
#include "math/polygon.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(void);

    QGraphicsView* canvas(void);
    
private slots:
    void onPushPointSaveButton(void);
    void onPushLineSaveButton(void);
    void onPushPolygonSaveButton(void);
    void onPushPolygonAddButton(void);

private:
    void addPolygonPointsToListView(const Point &);
    void addObjectToListView(const Object &);
    void clearLineTextFields(void);
    void clearPointTextFields(void);
    void clearPolygonTextFields(void);
    void setObjectName(Point &);
    void setObjectName(Line &);
    void setObjectName(Polygon &);
    inline void listening(void);

    Ui::MainWindow *ui;
    Points points;
    QStringList pointsListNames;
    QStringList objectsListNames;
    QStringListModel *pointsList;
    QStringListModel *objectsList;
};

#endif // MAINWINDOW_H
