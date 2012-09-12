#include "app/mainwindow.h"
#include "ui_mainwindow.h"
#include "math/line.h"
#include "app/controller.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->saveLineButton, SIGNAL(pressed()), this,  SLOT(onPushLineSaveButton()));
    connect(ui->savePointButton, SIGNAL(pressed()), this, SLOT(onPushPointSaveButton()));
    connect(ui->savePolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonSaveButton()));
    connect(ui->addPolygonButton, SIGNAL(pressed()), this, SLOT(onPushPolygonAddButton()));
}

MainWindow::~MainWindow()
{
    points.clear();
    delete ui;
}

QGraphicsView* MainWindow::canvas(void)
{
    return ui->graphicsView;
}

void MainWindow::onPushLineSaveButton(void)
{
    double startX = ui->lineStartX->text().toDouble();
    double startY = ui->lineStartY->text().toDouble();
    double startZ = ui->lineStartZ->text().toDouble();
    
    double endX = ui->lineEndX->text().toDouble();
    double endY = ui->lineEndY->text().toDouble();
    double endZ = ui->lineEndZ->text().toDouble();

    Line line(Point(startX, startY, startZ), Point(endX, endY, endZ));

    Controller::instance()->addObject(line);
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();
    
    Point point(x, y, z);
    Controller::instance()->addObject(point);
}

void MainWindow::onPushPolygonSaveButton(void)
{
    int i;
    Polygon polygon;
    
    for (i=0; i < points.size(); i++) {
        polygon.addPoint(points[i]);
    }
    
    if (!points.empty()) {
        Controller::instance()->addObject(polygon);
        points.clear();
    }
}

void MainWindow::onPushPolygonAddButton(void)
{
    double x = ui->polygonX->text().toDouble();
    double y = ui->polygonY->text().toDouble();
    double z = ui->polygonZ->text().toDouble();
    Point point(x, y, z);
    pointNames.append("Point");
   
    // TODO: Coding Horror!
    if (pointsList) {
        delete pointsList;
    }
    
    pointsList = new QStringListModel(pointNames);
    ui->pointsListView->setModel(pointsList);

    points.push_back(point);
}
