#include "app/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Point wMax(100.0, 100.0, 0.0);
    Point wMin(-100.0, -100.0, 0.0);
    window = new Window(wMin, wMax);

    ui->setupUi(this);
    displayFile = new DisplayFile();
    viewPort = new ViewPort(this->canvas(), window);
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
    delete viewPort;
    delete displayFile;
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

    displayFile->insertObject(line, name);
    
    addObjectToListView(line);

    clearLineTextFields();
    
    viewPort->draw(displayFile->objects());
}

void MainWindow::onPushPointSaveButton(void)
{
    double x = ui->pointX->text().toDouble();
    double y = ui->pointY->text().toDouble();
    double z = ui->pointZ->text().toDouble();
    
    QString name = ui->pointName->text();
    
    Point *point = new Point(x, y, z);
    
    displayFile->insertObject(point, name);
    
    addObjectToListView(point);

    clearPointTextFields();
    
    viewPort->draw(displayFile->objects());
}

void MainWindow::onPushPolygonSaveButton(void)
{
    int i;
    QString name = ui->polygonName->text();
    
    Polygon *polygon = new Polygon();
    polygon->name(name);
    
    for (i=0; i < points.size(); i++) {
        polygon->addPoint(points[i]);
    }
    
    if (!points.empty()) {
        displayFile->insertObject(polygon, name);
        points.clear();
        pointsListNames.clear();
    }
    
    addObjectToListView(polygon);
    
    clearPolygonTextFields();
    
    viewPort->draw(displayFile->objects());
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

void MainWindow::addObjectToListView(Object *object)
{
    objectsListNames.append(object->name());
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
