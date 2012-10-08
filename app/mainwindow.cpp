#include "app/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    viewPort = new ViewPort(this->canvas(), &displayFile);
    parser = new Parser(&displayFile);

    pointsList = new QStringListModel();
    objectsList = new QStringListModel();
    transformationsList = new QStringListModel();

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

    Object* triangle = new Object(POLYGON, 0, 255, 0);
    triangle->addPoint(50, -50, 0);
    triangle->addPoint(100, 50, 0);
    triangle->addPoint(100, 150, 0);
    addToObjectsList(triangle, QString("triangle"));

    Object* square = new Object(POLYGON, 255, 0, 0);
    square->addPoint(-50, -50, 0);
    square->addPoint(-150, -50, 0);
    square->addPoint(-150, -150, 0);
    square->addPoint(-50, -150, 0);
    addToObjectsList(square, QString("square"));

    tmpObject = 0;

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
    pointsListNames.clear();
    delete tmpObject;
    delete objectsList;
    delete transformationsList;
    delete pointsList;
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
    connect(ui->addPolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonAddButton()));
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
    if (tmpObject) {
        QString name = ui->polygonName->text();
        Object *polygon = new Object(POLYGON);
        *polygon = *tmpObject;
        addToObjectsList(polygon, name);
        delete tmpObject;
        tmpObject = 0;
    }
    clearPolygonTextFields();
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

void MainWindow::onPushPolygonAddButton(void)
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
    Point point(x, y, z);
    addToPointsList(point);
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
    objectPosition = index.row();
    Object* obj = displayFile.getObjectAt(objectPosition);
    if (obj->type() == POINT) {
        ui->selectedObjType->setText("Point");
    } else if (obj->type() == LINE) {
        ui->selectedObjType->setText("Line");
    } else {
        ui->selectedObjType->setText("Polygon");
    }
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

void MainWindow::addToObjectsList(Object *object, QString name)
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
}

void MainWindow::addToTransformationsList(QString transformation)
{
    transformationsListNames.append(transformation);
    transformationsList->setStringList(transformationsListNames);
    ui->transformationsListView->setModel(transformationsList);
}

void MainWindow::deleteFromTransformationsList(unsigned int index)
{
    transformationsListNames.removeAt(index);
    transformationsList->setStringList(transformationsListNames);
    ui->transformationsListView->setModel(transformationsList);
}

void MainWindow::addToPointsList(const Point &point)
{
    pointsListNames.append(QString::fromStdString(point.toString()));
    pointsList->setStringList(pointsListNames);
    ui->pointsListView->setModel(pointsList);
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
    pointsListNames.clear();
    pointsList->setStringList(pointsListNames);
    ui->pointsListView->setModel(pointsList);
}

void MainWindow::onActionImportObjTriggered(void)
{
    //parser->importFromObj("file.obj");
}

void MainWindow::onActionExportObjTriggered(void)
{
    parser->exportToObj("new-file.obj");
}
