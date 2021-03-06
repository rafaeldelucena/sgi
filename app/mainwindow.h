#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <QPushButton>
#include <QPainter>

#include "view/formas.h"
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
    void onPushPolygonAddPointButton(void);
    void onPushCurveSaveButton(void);
    void onPushCurveAddPointButton(void);
    void onPushDeleteButton(void);
    void onPushMoveUpButton(void);
    void onPushMoveLeftButton(void);
    void onPushMoveDownButton(void);
    void onPushMoveRightButton(void);
    void onPushResetWindowButton(void);
    void onPushUpdateWindowButton(void);
    void onPushRotateWindowButton(void);
    void onPushZoomInButton(void);
    void onPushZoomOutButton(void);
    void onSelectObject(const QModelIndex &);
    void onSelectTransformation(const QModelIndex &);
    void onPushTransformationAddButton(void);
    void onPushTransformationDeleteButton(void);
    void onPushTransformationsApplyButton(void);
    void onActionImportObjTriggered(void);
    void onActionExportObjTriggered(void);
    void onFilledBoxToggled(bool checked);

private:
    void addToPolygonPointsList(const QString & name);
    void addToCurvePointsList(const QString & name);
    void addToObjectsList(Object *object, const QString & name);
    void addToTransformationsList(QString transformation);
    void addToSelectedObjectPointsList(QString point);
    void deleteFromObjectsList(unsigned int index);
    void deleteFromTransformationsList(unsigned int index);
    void clearLineTextFields(void);
    void clearPointTextFields(void);
    void clearPolygonTextFields(void);
    void clearCurveTextFields(void);
    void clearObjectsPointsList(void);
    void updateWindowPoints(void);

    unsigned int objectPosition;
    unsigned int transformationPosition;
    bool objectFilled;

    inline void listen(void);

    Ui::MainWindow *ui;
    QStringList polygonPointsListNames;
    QStringList curvePointsListNames;
    QStringList objectsListNames;
    QStringList transformationsListNames;
    QStringList selectedObjPointsListNames;
    QStringListModel *polygonPointsList;
    QStringListModel *curvePointsList;
    QStringListModel *objectsList;
    QStringListModel *transformationsList;
    QStringListModel *selectedObjPointsList;

    Object* tmpObject;
    DisplayFile displayFile;
    ViewPort *viewPort;
};

#endif // MAINWINDOW_H
