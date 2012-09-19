#include "app/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    Point wMax(100.0, 100.0, 0.0);
    Point wMin(-100.0, -100.0, 0.0);
    window = new Window(wMin, wMax);

    ui->setupUi(this);
    viewPort = new ViewPort(this->canvas(), window);
    pointsList = new QStringListModel();
    objectsList = new QStringListModel();

    //QPainter painter(ui->widgetQPainter);
    //painter.setPen(QPen(Qt::black, 3));
    //painter.drawLine(1,1,50,50);
    
    //ui->widgetQPainter

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
    
    viewPort->draw(line);
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
    
    viewPort->draw(point);
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
        viewPort->draw(polygon);
    }
    
    pointsListNames.clear();
    clearPolygonTextFields();
    
}

void MainWindow::onPushDeleteButton(void)
{
    if (!displayFile.objects().empty()) {
        removeObjectToListViewAt(objectPosition);
        displayFile.removeObjectAt(objectPosition); 
        reDrawObjectsOnScreen();
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
    window->up(1.0);
    reDrawObjectsOnScreen();
}

void MainWindow::onPushMoveLeftButton(void)
{
    window->left(1.0);
    reDrawObjectsOnScreen();
}

void MainWindow::onPushMoveDownButton(void)
{
    window->down(1.0);
    reDrawObjectsOnScreen();
}

void MainWindow::onPushMoveRightButton(void)
{
    window->right(1.0);
    reDrawObjectsOnScreen();
}

void MainWindow::onPushZoomInButton(void)
{
    window->shrink(1.0);
    reDrawObjectsOnScreen();
}

void MainWindow::onPushZoomOutButton(void)
{
    window->stretch(1.0);
    reDrawObjectsOnScreen();
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

void MainWindow::reDrawObjectsOnScreen(void)
{
    if (!displayFile.objects().empty()) {
        viewPort->draw(displayFile.objects());
    }
}
