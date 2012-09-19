#include "app/mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{

    Point wMax(1.0, 1.0, 0.0);
    Point wMin(-1.0, -1.0, 0.0);
    window = new Window(wMin, wMax);

    ui->setupUi(this);

    viewPort = new ViewPort(this->canvas(), window, &displayFile);

    pointsList = new QStringListModel();
    objectsList = new QStringListModel();
    objectPosition = 0;

    Object *line = new Object(LINE);
    line->addPoint(Point(-50, 0, 0));
    line->addPoint(Point(50, 0, 0));
    addObjectToListView(line, QString("x axis"));

    Object *line1 = new Object(LINE);
    line1->addPoint(Point(0, -50, 0));
    line1->addPoint(Point(0, 50, 0));
    addObjectToListView(line, QString("y axis"));

    viewPort->draw();

    listening();
}

MainWindow::~MainWindow()
{
    points.clear();
    pointsListNames.clear();
    delete objectsList;
    delete pointsList;
    delete viewPort;
    delete ui;
    delete window;
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
    connect(ui->centerViewPortButton, SIGNAL(pressed()), this, SLOT(onPushCenterViewPortButton()));
    connect(ui->zoomInButton, SIGNAL(pressed()), this, SLOT(onPushZoomInButton()));
    connect(ui->zoomOutButton, SIGNAL(pressed()), this, SLOT(onPushZoomOutButton()));
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
        objectPosition = 0;
    }
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
    window->up(ui->moveStep->text().toDouble());
    viewPort->draw();
}

void MainWindow::onPushMoveLeftButton(void)
{
    window->left(ui->moveStep->text().toDouble());
    viewPort->draw();
}

void MainWindow::onPushMoveDownButton(void)
{
    window->down(ui->moveStep->text().toDouble());
    viewPort->draw();
}

void MainWindow::onPushCenterViewPortButton(void)
{
    window->centralize();
    viewPort->draw();
}

void MainWindow::onPushMoveRightButton(void)
{
    window->right(ui->moveStep->text().toDouble());
    viewPort->draw();
}

#include <iostream>
void MainWindow::onPushZoomInButton(void)
{
    window->decrease(ui->zoomFactor->text().toDouble());
    viewPort->draw();
}

void MainWindow::onPushZoomOutButton(void)
{
    window->enlarge(ui->zoomFactor->text().toDouble());
    viewPort->draw();
}

void MainWindow::onSelectObject(const QModelIndex & index)
{
    objectPosition = index.row();
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
