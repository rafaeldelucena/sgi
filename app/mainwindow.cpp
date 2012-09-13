#include "app/mainwindow.h"
#include "ui_mainwindow.h"
#include "math/line.h"
#include "app/controller.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pointsList = new QStringListModel();
    objectsList = new QStringListModel();

    listening();
}

MainWindow::~MainWindow()
{
    points.clear();
    pointsListNames.clear();
    delete objectsList;
    delete pointsList;
    delete ui;
}

QGraphicsView* MainWindow::canvas(void)
{
    return ui->graphicsView;
}

inline void MainWindow::listening(void)
{
    connect(ui->saveLineButton, SIGNAL(pressed()), this,  SLOT(onPushLineSaveButton()));
    connect(ui->savePointButton, SIGNAL(pressed()), this, SLOT(onPushPointSaveButton()));
    connect(ui->savePolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonSaveButton()));
    connect(ui->addPolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonAddButton()));
}

void MainWindow::onPushLineSaveButton(void)
{
    double startX = ui->lineStartX->text().toDouble();
    double startY = ui->lineStartY->text().toDouble();
    double startZ = ui->lineStartZ->text().toDouble();
    
    double endX = ui->lineEndX->text().toDouble();
    double endY = ui->lineEndY->text().toDouble();
    double endZ = ui->lineEndZ->text().toDouble();

    Line line(Point(startX, startY, startZ), Point(endX, endY, endZ), ui->lineName->text());


    Controller::instance()->addObject(line);
    
    addObjectToListView(line);

    clearLineTextFields();
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();
    
    Point point(x, y, z, ui->pointName->text());
    Controller::instance()->addObject(point);
    
    addObjectToListView(point);

    clearPointTextFields();
}

void MainWindow::onPushPolygonSaveButton(void)
{
    int i;
    Polygon polygon(ui->polygonName->text());
    
    for (i=0; i < points.size(); i++) {
        polygon.addPoint(points[i]);
    }
    
    if (!points.empty()) {
        Controller::instance()->addObject(polygon);
        points.clear();
        pointsListNames.clear();
    }
    
    addObjectToListView(polygon);
    clearPolygonTextFields();
}

void MainWindow::onPushPolygonAddButton(void)
{
    double x = ui->polygonX->text().toDouble();
    double y = ui->polygonY->text().toDouble();
    double z = ui->polygonZ->text().toDouble();
    Point point(x, y, z);
    
    points.push_back(point);

    addPolygonPointsToListView(point);
}

void MainWindow::addObjectToListView(const Object &object)
{
    objectsListNames.append(object.name());
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
}

void MainWindow::addPolygonPointsToListView(const Point& point)
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
