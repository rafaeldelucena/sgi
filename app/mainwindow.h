#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QPushButton>
#include <QPainter>

#include "app/formas.h"

#include "view/displayfile.h"
#include "view/viewport.h"

#include "ui_mainwindow.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow(void);

    Canhamo* canvas(void);

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
    void onPushResetWindowButton(void);
    void onPushUpdateWindowButton(void);
    void onPushZoomInButton(void);
    void onPushZoomOutButton(void);
    void onSelectObject(const QModelIndex &);
    void onPushTransformationAddButton(void);
    void onPushTransformationsApplyButton(void);

private:
    void addToPointsList(const Point &point);
    void addToObjectsList(Object *object, QString name);
    void addToTransformationsList(QString transformation);
    void removeObjectToListViewAt(unsigned int index);
    void clearLineTextFields(void);
    void clearPointTextFields(void);
    void clearPolygonTextFields(void);
    void updateWindowPoints(void);

    inline void listening(void);

    Ui::MainWindow *ui;
    QStringList pointsListNames;
    QStringList objectsListNames;
    QStringList transformationsListNames;
    QStringListModel *pointsList;
    QStringListModel *objectsList;
    QStringListModel *transformationsList;

    Points points;
    DisplayFile displayFile;
    ViewPort *viewPort;
    Object *xAxis, *yAxis, *zAxis;
    unsigned int objectPosition;
};

#endif // MAINWINDOW_H
