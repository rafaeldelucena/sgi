#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QStringListModel>
#include <QPushButton>

#include "app/formas.h"

#include "view/displayfile.h"
#include "view/window.h"
#include "view/viewport.h"

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
    void onPushDeleteButton(void);
    void onPushMoveUpButton(void);
    void onPushMoveLeftButton(void);
    void onPushMoveDownButton(void);
    void onPushMoveRightButton(void);
    void onPushCenterViewPortButton(void);
    void onPushZoomInButton(void);
    void onPushZoomOutButton(void);
    void onSelectObject(const QModelIndex &);

private:
    void addPolygonPointsToListView(const Point &point);
    void addObjectToListView(Object *object);
    void removeObjectToListViewAt(unsigned int index);
    void reDrawObjectsOnScreen(void);
    void clearLineTextFields(void);
    void clearPointTextFields(void);
    void clearPolygonTextFields(void);
    
    inline void listening(void);

    Ui::MainWindow *ui;
    QStringList pointsListNames;
    QStringList objectsListNames;
    QStringListModel *pointsList;
    QStringListModel *objectsList;

    Points points;
    DisplayFile displayFile;
    Window *window;
    ViewPort *viewPort;
    unsigned int objectPosition;
};

#endif // MAINWINDOW_H
