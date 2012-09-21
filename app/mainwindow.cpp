#include "app/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    viewPort = new ViewPort(this->canvas(), &displayFile);

    pointsList = new QStringListModel();
    objectsList = new QStringListModel();
    objectPosition = 0;

    xAxis = new Object(LINE);
    xAxis->addPoint(Point(-150, 0, 0));
    xAxis->addPoint(Point(150, 0, 0));
    addObjectToListView(xAxis, QString("x axis"));

    yAxis = new Object(LINE);
    yAxis->addPoint(Point(0, -150, 0));
    yAxis->addPoint(Point(0, 150, 0));
    addObjectToListView(yAxis, QString("y axis"));

    /*
    zAxis = new Object(LINE);
    zAxis->addPoint(Point(0, 0, 0));
    zAxis->addPoint(Point(0, 0, 200));
    addObjectToListView(zAxis, QString("z axis"));
    */

    listening();

    viewPort->draw();
    updateWindowPoints();
}

MainWindow::~MainWindow()
{
    if (xAxis) delete xAxis;
    if (yAxis) delete yAxis;
    if (zAxis) delete zAxis;
    points.clear();
    pointsListNames.clear();
    delete objectsList;
    delete pointsList;
    delete viewPort;
    delete ui;
}

Canhamo* MainWindow::canvas(void)
{
    return ui->widgetCanhamo;
}

inline void MainWindow::listening(void)
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
    connect(ui->zoomInButton, SIGNAL(pressed()), this, SLOT(onPushZoomInButton()));
    connect(ui->zoomOutButton, SIGNAL(pressed()), this, SLOT(onPushZoomOutButton()));
    connect(ui->transformationAddButton, SIGNAL(pressed()), this, SLOT(onPushTransformationAddButton()));
    connect(ui->transformationsApplyButton, SIGNAL(pressed()), this, SLOT(onPushTransformationsApplyButton()));
    connect(ui->objectsListView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(onSelectObject(const QModelIndex &)));
}

void MainWindow::onPushLineSaveButton(void)
{
    double startX = ui->lineStartX->text().toDouble();
    double startY = ui->lineStartY->text().toDouble();
    double startZ = ui->lineStartZ->text().toDouble();

    double endX = ui->lineEndX->text().toDouble();
    double endY = ui->lineEndY->text().toDouble();
    double endZ = ui->lineEndZ->text().toDouble();

    QString name = ui->lineName->text();

    Object *line = new Object(LINE);
    line->addPoint(Point(startX, startY, startZ));
    line->addPoint(Point(endX, endY, endZ));

    addObjectToListView(line, name);

    clearLineTextFields();

    viewPort->draw();
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();

    QString name = ui->pointName->text();

    Object *point = new Object(POINT);
    point->addPoint(Point(x, y, z));

    addObjectToListView(point, name);

    clearPointTextFields();

    viewPort->draw();
}

void MainWindow::onPushPolygonSaveButton(void)
{

    if (!points.empty()) {
        QString name = ui->polygonName->text();
        Object *polygon = new Object(POLYGON);
        unsigned int i;
        for (i=0; i < points.size(); i++) {
            polygon->addPoint(points[i]);
        }
        points.clear();
        addObjectToListView(polygon, name);
    }

    pointsListNames.clear();
    clearPolygonTextFields();

    viewPort->draw();
}

void MainWindow::onPushDeleteButton(void)
{
    if (displayFile.objectsSize() > 0) {
        removeObjectToListViewAt(objectPosition);
        displayFile.removeObjectAt(objectPosition);
        viewPort->draw();
    }
    objectPosition = 0;
}

void MainWindow::onPushPolygonAddButton(void)
{
    double x = ui->polygonX->text().toDouble();
    double y = ui->polygonY->text().toDouble();
    double z = ui->polygonZ->text().toDouble();
    Point point(x, y, z);

    points.push_back(point);

    addPointsToPointsList(point);
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
}

void MainWindow::onPushTransformationsApplyButton(void)
{
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

void MainWindow::addObjectToListView(Object *object, QString name)
{
    displayFile.insertObject(object, name);
    objectsListNames.append(name);
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
}

void MainWindow::removeObjectToListViewAt(unsigned int index)
{
    objectsListNames.removeAt(index);
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
}

void MainWindow::addPointsToPointsList(const Point& point)
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
}
