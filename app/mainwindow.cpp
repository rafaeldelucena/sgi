#include "app/mainwindow.h"
#include "ui_mainwindow.h"

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

    Line *line = new Line(Point(-50, 0, 0), Point(50, 0, 0));
    displayFile.insertObject(line, QString("x axis"));
    addObjectToListView(line);

    Line *line1 = new Line(Point(0, -50, 0), Point(0, 50, 0));
    displayFile.insertObject(line1, QString("y axis"));
    addObjectToListView(line);

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
    connect(ui->deleteButton, SIGNAL(pressed()), this, SLOT(onPushDeleteButton()));
    connect(ui->moveUpButton, SIGNAL(pressed()), this, SLOT(onPushMoveUpButton()));
    connect(ui->moveLeftButton, SIGNAL(pressed()), this, SLOT(onPushMoveLeftButton()));
    connect(ui->moveRightButton, SIGNAL(pressed()), this, SLOT(onPushMoveRightButton()));
    connect(ui->moveDownButton, SIGNAL(pressed()), this, SLOT(onPushMoveDownButton()));
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

    Line *line = new Line(Point(startX, startY, startZ), Point(endX, endY, endZ));

    displayFile.insertObject(line, name);
    
    addObjectToListView(line);

    clearLineTextFields();
    
    viewPort->draw();
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();
    
    QString name = ui->pointName->text();
    
    Point *point = new Point(x, y, z);
    
    displayFile.insertObject(point, name);
    
    addObjectToListView(point);

    clearPointTextFields();
    
    viewPort->draw();
}

void MainWindow::onPushPolygonSaveButton(void)
{
    
    if (!points.empty()) {
        QString name = ui->polygonName->text();
        Polygon *polygon = new Polygon();
        unsigned int i;
        for (i=0; i < points.size(); i++) {
            polygon->addPoint(points[i]);
        }
        displayFile.insertObject(polygon, name);
        points.clear();
        addObjectToListView(polygon);
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

    addPolygonPointsToListView(point);
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

void MainWindow::addObjectToListView(Object *object)
{
    objectsListNames.append(object->name());
    objectsList->setStringList(objectsListNames);
    ui->objectsListView->setModel(objectsList);
}

void MainWindow::removeObjectToListViewAt(unsigned int index)
{
    objectsListNames.removeAt(index);
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
