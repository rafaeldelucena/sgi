#include "app/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewPort = new ViewPort(this->canvas(), &displayFile);

    polygonPointsList = new QStringListModel();
    curvePointsList = new QStringListModel();
    objectsList = new QStringListModel();
    transformationsList = new QStringListModel();
    selectedObjPointsList = new QStringListModel();

    objectPosition = 0;
    transformationPosition = 0;

    Object* xAxis = new Object(LINE);
    xAxis->addPoint(-150, 0, 0);
    xAxis->addPoint(150, 0, 0);
    addToObjectsList(xAxis, QString("x axis"));

    Object* yAxis = new Object(LINE);
    yAxis->addPoint(0, -150, 0);
    yAxis->addPoint(0, 150, 0);
    addToObjectsList(yAxis, QString("y axis"));

    Object* new_line = new Object(LINE);
    new_line->addPoint(124, 124, 0);
    new_line->addPoint(169, 169, 0);
    addToObjectsList(new_line, QString("new_line"));

    Object* triangle = new Object(POLYGON, 0, 255, 0);
    triangle->addPoint(100, 150, 0);
    triangle->addPoint(150, 50, 0);
    triangle->addPoint(50, 50, 0);
    triangle->addPoint(100, 150, 0);
    addToObjectsList(triangle, QString("triangle"));

    Object* square = new Object(POLYGON, 255, 0, 0);
    square->addPoint(-75, -50, 0);
    square->addPoint(-50, -150, 0);
    square->addPoint(-150, -150, 0);
    square->addPoint(-100, -50, 0);
    square->addPoint(-75, -50, 0);
    addToObjectsList(square, QString("square"));

    Object* pentagon = new Object(POLYGON, 255, 0, 0);
    pentagon->addPoint(-60, 120, 0);
    pentagon->addPoint(-10, 60, 0);
    pentagon->addPoint(-20, 10, 0);
    pentagon->addPoint(-100, 10, 0);
    pentagon->addPoint(-110, 60, 0);
    pentagon->addPoint(-60, 120, 0);
    addToObjectsList(pentagon, QString("pentagon"));

    Object* curve = new Object(CURVE, 0, 0, 255);
    curve->addPoint(50, -100, 0);
    curve->addPoint(200, 0 ,0);
    curve->addPoint(0, 0, 0);
    curve->addPoint(100,-150, 0);
    addToObjectsList(curve, QString("loop"));

    tmpObject = 0;
    objectFilled = false;

    /*
    zAxis = new Object(LINE);
    zAxis->addPoint(0, 0, 0);
    zAxis->addPoint(0, 0, 200);
    addToObjectsList(zAxis, QString("z axis"));
    */

    listen();

    viewPort->draw();
    updateWindowPoints();
}

MainWindow::~MainWindow()
{
    polygonPointsListNames.clear();
    curvePointsListNames.clear();
    delete tmpObject;
    delete objectsList;
    delete transformationsList;
    delete selectedObjPointsList;
    delete polygonPointsList;
    delete curvePointsList;
    delete viewPort;
    delete ui;
}

Canhamo* MainWindow::canvas(void)
{
    return ui->widgetCanhamo;
}

inline void MainWindow::listen(void)
{
    connect(ui->saveLineButton, SIGNAL(pressed()), this,  SLOT(onPushLineSaveButton()));
    connect(ui->savePointButton, SIGNAL(pressed()), this, SLOT(onPushPointSaveButton()));
    connect(ui->savePolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonSaveButton()));
    connect(ui->addPolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonAddPointButton()));
    connect(ui->saveCurveButton, SIGNAL(pressed()), this, SLOT(onPushCurveSaveButton()));
    connect(ui->addCurvePointButton, SIGNAL(pressed()), this, SLOT(onPushCurveAddPointButton()));
    connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(onPushDeleteButton()));
    connect(ui->moveUpButton, SIGNAL(pressed()), this, SLOT(onPushMoveUpButton()));
    connect(ui->moveLeftButton, SIGNAL(pressed()), this, SLOT(onPushMoveLeftButton()));
    connect(ui->moveRightButton, SIGNAL(pressed()), this, SLOT(onPushMoveRightButton()));
    connect(ui->moveDownButton, SIGNAL(pressed()), this, SLOT(onPushMoveDownButton()));
    connect(ui->resetWindowButton, SIGNAL(pressed()), this, SLOT(onPushResetWindowButton()));
    connect(ui->updateWindowButton, SIGNAL(pressed()), this, SLOT(onPushUpdateWindowButton()));
    connect(ui->rotateWindowButton, SIGNAL(pressed()), this, SLOT(onPushRotateWindowButton()));
    connect(ui->zoomInButton, SIGNAL(pressed()), this, SLOT(onPushZoomInButton()));
    connect(ui->zoomOutButton, SIGNAL(pressed()), this, SLOT(onPushZoomOutButton()));
    connect(ui->transformationAddButton, SIGNAL(pressed()), this, SLOT(onPushTransformationAddButton()));
    connect(ui->transformationDeleteButton, SIGNAL(pressed()), this, SLOT(onPushTransformationDeleteButton()));
    connect(ui->transformationsApplyButton, SIGNAL(pressed()), this, SLOT(onPushTransformationsApplyButton()));
    connect(ui->objectsListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onSelectObject(const QModelIndex &)));
    connect(ui->transformationsListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onSelectTransformation(const QModelIndex &)));
    connect(ui->importObjAction, SIGNAL(triggered()), this, SLOT(onActionImportObjTriggered()));
    connect(ui->exportObjAction, SIGNAL(triggered()), this, SLOT(onActionExportObjTriggered()));
    connect(ui->filledBox, SIGNAL(toggled(bool)), this, SLOT(onFilledBoxToggled(bool)));
}

void MainWindow::onPushLineSaveButton(void)
{
    double startX = ui->lineStartX->text().toDouble();
    double startY = ui->lineStartY->text().toDouble();
    double startZ = ui->lineStartZ->text().toDouble();

    double endX = ui->lineEndX->text().toDouble();
    double endY = ui->lineEndY->text().toDouble();
    double endZ = ui->lineEndZ->text().toDouble();

    int r = ui->lineColorR->text().toInt();
    int g = ui->lineColorG->text().toInt();
    int b = ui->lineColorB->text().toInt();

    QString name = ui->lineName->text();

    Object *line = new Object(LINE, r, g, b);
    line->addPoint(startX, startY, startZ);
    line->addPoint(endX, endY, endZ);

    addToObjectsList(line, name);

    clearLineTextFields();

    viewPort->draw();
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();

    int r = ui->pointColorR->text().toInt();
    int g = ui->pointColorG->text().toInt();
    int b = ui->pointColorB->text().toInt();

    QString name = ui->pointName->text();

    Object *point = new Object(POINT, r, g, b);
    point->addPoint(x, y, z);

    addToObjectsList(point, name);

    clearPointTextFields();

    viewPort->draw();
}

void MainWindow::onPushPolygonSaveButton(void)
{
    if (tmpObject && polygonPointsListNames.size() >= 3) {
        QString name = ui->polygonName->text();
        Object *polygon = new Object(POLYGON);
        *polygon = *tmpObject;
        polygon->fill(objectFilled);
        addToObjectsList(polygon, name);
        delete tmpObject;
        tmpObject = 0;
    }
    clearPolygonTextFields();
    viewPort->draw();
}

void MainWindow::onPushCurveSaveButton(void)
{
    if (tmpObject && curvePointsListNames.size() >= 4) {
        QString name = ui->curveName->text();
        Object *curve = new Object(CURVE);
        *curve = *tmpObject;
        addToObjectsList(curve, name);
        delete tmpObject;
        tmpObject = 0;
    }
    clearCurveTextFields();
    viewPort->setCurveSteps(ui->curvePrecision->text().toInt());
    viewPort->draw();
}

void MainWindow::onPushDeleteButton(void)
{
    if (displayFile.objectsCount() > 0) {
        deleteFromObjectsList(objectPosition);
        displayFile.removeObjectAt(objectPosition);
        viewPort->draw();
    }
    objectPosition = 0;
}

void MainWindow::onPushPolygonAddPointButton(void)
{
    if (!tmpObject) {
        int r = ui->polygonColorR->text().toInt();
        int g = ui->polygonColorG->text().toInt();
        int b = ui->polygonColorB->text().toInt();
        tmpObject = new Object(POLYGON, r, g, b);
    }
    double x = ui->polygonX->text().toDouble();
    double y = ui->polygonY->text().toDouble();
    double z = ui->polygonZ->text().toDouble();

    tmpObject->addPoint(x, y, z);
    std::stringstream s;
    s << "Point: " << x << "," << y << "," <<  z;
    addToPolygonPointsList(QString::fromStdString(s.str()));
}

void MainWindow::onPushCurveAddPointButton(void)
{
    if (!tmpObject) {
        int r = ui->curveColorR->text().toInt();
        int g = ui->curveColorG->text().toInt();
        int b = ui->curveColorB->text().toInt();
        tmpObject = new Object(CURVE, r, g, b);
    }
    double x = ui->curveX->text().toDouble();
    double y = ui->curveY->text().toDouble();
    double z = ui->curveZ->text().toDouble();

    tmpObject->addPoint(x, y, z);
    
    std::stringstream s;
    s << "Point: " << x << "," << y << "," <<  z;
    addToCurvePointsList(QString::fromStdString(s.str()));
}

void MainWindow::onPushMoveUpButton(void)
{
    viewPort->up(ui->moveStep->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushMoveLeftButton(void)
{
    viewPort->left(ui->moveStep->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushMoveDownButton(void)
{
    viewPort->down(ui->moveStep->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushResetWindowButton(void)
{
    viewPort->reset();
    updateWindowPoints();
}

void MainWindow::onPushUpdateWindowButton(void)
{
    viewPort->reset(ui->windowMinX->text().toDouble(), ui->windowMinY->text().toDouble(),
            ui->windowMaxX->text().toDouble(), ui->windowMaxY->text().toDouble());
}

void MainWindow::onPushRotateWindowButton(void)
{
    viewPort->rotate(ui->rotateAngle->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushMoveRightButton(void)
{
    viewPort->right(ui->moveStep->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushZoomInButton(void)
{
    viewPort->zoomIn(ui->zoomFactor->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushZoomOutButton(void)
{
    viewPort->zoomOut(ui->zoomFactor->text().toDouble());
    updateWindowPoints();
}

void MainWindow::onPushTransformationAddButton(void)
{

    QString transformation = QString("");
    if (displayFile.objectsCount() > 0) {

        if (ui->transformTranslate->isChecked()) {

            QStringList params = ui->transformationParams->text().split(",");

            if (params.size() == 2) {
                addToTransformationsList(QString("translate ")+params.at(0)+QString(",")+params.at(1));
            }

        } else if (ui->transformRotateOrigin->isChecked()) {

            QStringList params = ui->transformationParams->text().split(",");

            if (params.size() == 1) {
                addToTransformationsList(QString("rotate_origin ")+params.at(0));
            }

        } else if (ui->transformRotateCenter->isChecked()) {

            QStringList params = ui->transformationParams->text().split(",");

            if (params.size() == 1) {
                addToTransformationsList(QString("rotate_center ")+params.at(0));
            }

        } else if (ui->transformRotatePoint->isChecked()) {

            QStringList params = ui->transformationParams->text().split(",");

            if (params.size() == 3) {
                addToTransformationsList(QString("rotate_point "+params.at(0)+QString(",")+
                                                                  params.at(1)+QString(",")+
                                                                  params.at(2)));
            }
        } else if (ui->transformScale->isChecked()) {

            QStringList params = ui->transformationParams->text().split(",");

            if (params.size() == 2) {
                addToTransformationsList(QString("scale "+params.at(0)+QString(",")+params.at(1)));
            }
        }
    }
}

void MainWindow::onPushTransformationDeleteButton(void)
{
    deleteFromTransformationsList(transformationPosition);
}

void MainWindow::onPushTransformationsApplyButton(void)
{
    Object* obj = displayFile.getObjectAt(objectPosition);
    for (int i = 0; i < transformationsListNames.size(); i++) {

        QStringList t = transformationsListNames.at(i).split(" ");

        if (t.at(0) == "rotate_origin") {

            obj->rotateOrigin(t.at(1).toDouble());

        } else if (t.at(0) == "rotate_center") {

            obj->rotateCenter(t.at(1).toDouble());

        } else if (t.at(0) == "rotate_point") {

            QStringList p = t.at(1).split(",");
            obj->rotatePoint(p.at(0).toDouble(), Point(p.at(1).toDouble(), p.at(2).toDouble()));

        } else if (t.at(0) == "scale") {

            QStringList p = t.at(1).split(",");
            obj->scale(Point(p.at(0).toDouble(), p.at(1).toDouble()));

        } else if (t.at(0) == "translate") {

            QStringList p = t.at(1).split(",");
            obj->translate(Point(p.at(0).toDouble(), p.at(1).toDouble()));

        }
    }
    viewPort->draw();
}

void MainWindow::onSelectObject(const QModelIndex & index)
{
    clearObjectsPointsList();
    objectPosition = index.row();
    Object* obj = displayFile.getObjectAt(objectPosition);
    if (obj->type() == POINT) {
        ui->selectedObjType->setText("Point");
    } else if (obj->type() == LINE) {
        ui->selectedObjType->setText("Line");
    } else if (obj->type() == POLYGON) {
        ui->selectedObjType->setText("Polygon");
    } else {
        ui->selectedObjType->setText("Curve");
    }
    for (unsigned i=0; i < obj->pointsCount(); i++) {
	addToSelectedObjectPointsList(QString::fromStdString(obj->point(i).toString()));	  }
}

void MainWindow::onSelectTransformation(const QModelIndex & index)
{
    transformationPosition = index.row();
}

void MainWindow::updateWindowPoints(void)
{
    QString minx, miny, maxx, maxy;
    minx = minx.setNum(viewPort->minWindowPoint().x());
    miny = miny.setNum(viewPort->minWindowPoint().y());
    maxx = maxx.setNum(viewPort->maxWindowPoint().x());
    maxy = maxy.setNum(viewPort->maxWindowPoint().y());

    ui->windowMinX->setText(minx);
    ui->windowMinY->setText(miny);
    ui->windowMaxX->setText(maxx);
    ui->windowMaxY->setText(maxy);
}

void MainWindow::addToObjectsList(Object *object, const QString & name)
{
    displayFile.insertObject(object);
    objectsListNames.append(name);
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
}

void MainWindow::deleteFromObjectsList(unsigned int index)
{
    objectsListNames.removeAt(index);
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
    clearObjectsPointsList();
}

void MainWindow::addToTransformationsList(QString transformation)
{
    transformationsListNames.append(transformation);
    transformationsList->setStringList(transformationsListNames);
    ui->transformationsListView->setModel(transformationsList);
}

void MainWindow::addToSelectedObjectPointsList(QString point)
{
    selectedObjPointsListNames.append(point);
    selectedObjPointsList->setStringList(selectedObjPointsListNames);
    ui->selectedObjPointsListView->setModel(selectedObjPointsList);
}

void MainWindow::clearObjectsPointsList(void)
{
    selectedObjPointsListNames.clear();
    selectedObjPointsList->setStringList(selectedObjPointsListNames);
    ui->selectedObjPointsListView->setModel(selectedObjPointsList);
}

void MainWindow::deleteFromTransformationsList(unsigned int index)
{
    transformationsListNames.removeAt(index);
    transformationsList->setStringList(transformationsListNames);
    ui->transformationsListView->setModel(transformationsList);
}

void MainWindow::addToPolygonPointsList(const QString & name)
{
    polygonPointsListNames.append(name);
    polygonPointsList->setStringList(polygonPointsListNames);
    ui->polygonPointsListView->setModel(polygonPointsList);
}

void MainWindow::addToCurvePointsList(const QString & name)
{
    curvePointsListNames.append(name);
    curvePointsList->setStringList(curvePointsListNames);
    ui->curvePointsListView->setModel(curvePointsList);
}

void MainWindow::clearPointTextFields(void)
{
    ui->pointX->clear();
    ui->pointY->clear();
    ui->pointZ->clear();

    ui->pointName->clear();
}

void MainWindow::clearLineTextFields(void)
{
    ui->lineStartX->clear();
    ui->lineStartY->clear();
    ui->lineStartZ->clear();

    ui->lineEndX->clear();
    ui->lineEndY->clear();
    ui->lineEndZ->clear();

    ui->lineName->clear();
}

void MainWindow::clearPolygonTextFields(void)
{
    ui->polygonX->clear();
    ui->polygonY->clear();
    ui->polygonZ->clear();

    ui->polygonName->clear();
    ui->filledBox->setChecked(false);
    polygonPointsListNames.clear();
    polygonPointsList->setStringList(polygonPointsListNames);
    ui->polygonPointsListView->setModel(polygonPointsList);
}

void MainWindow::clearCurveTextFields(void)
{
    ui->curveX->clear();
    ui->curveY->clear();
    ui->curveZ->clear();

    ui->curveName->clear();
    curvePointsListNames.clear();
    curvePointsList->setStringList(curvePointsListNames);
    ui->curvePointsListView->setModel(curvePointsList);
}

void MainWindow::onActionImportObjTriggered(void)
{
}

void MainWindow::onActionExportObjTriggered(void)
{
}

void MainWindow::onFilledBoxToggled(bool checked)
{
    objectFilled = checked;
}
