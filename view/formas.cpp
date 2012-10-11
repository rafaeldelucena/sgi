#include "view/formas.h"
#include <math.h>

#define PI 3.14159265

#include <iostream>

Object::Object(Shape type, int r, int g, int b)
{
    shape = type;
    color.r = r;
    color.g = g;
    color.b = b;
    clearTransformations();
    filled = false;
}

Object::~Object(void)
{
}

Shape Object::type(void) const
{
    return shape;
}

int Object::regionCode(double x, double y, double xmin, double ymin, double xmax, double ymax)
{
    const int INSIDE = 0; // 0000
    const int LEFT = 1;   // 0001
    const int RIGHT = 2;  // 0010
    const int BOTTOM = 4; // 0100
    const int TOP = 8;    // 1000

    int code = INSIDE;

    if (x < xmin)           // to the left of clip window
        code |= LEFT;
    else if (x > xmax)      // to the right of clip window
        code |= RIGHT;
    if (y < ymin)           // below the clip window
        code |= BOTTOM;
    else if (y > ymax)      // above the clip window
        code |= TOP;

    return code;
}

Object* Object::clip(double wmin_x, double wmin_y, double wmax_x, double wmax_y,
                     const Point& windowCenter, double vup, const Point& scale)
{

    if (shape == POINT) {

        Point p = this->point(0);
        p.updateSNC(windowCenter, vup, scale);

        // em coordenadas normalizadas, a viewport vai de -1 a 1
        if ( ((p.sncX() < -1) || (p.sncX() > 1)) || ((p.sncY() < -1) || (p.sncY() > 1)) ) {
            return 0;
        } else {
            Object* new_point = new Object(POINT, color.r, color.g, color.b);
            new_point->addPoint(p.sncX(), p.sncY(), 1);
            return new_point;
        }

    } else if (shape == LINE) {

        // cohen sutherland
        //const int INSIDE = 0; // 0000
        const int LEFT = 1;   // 0001
        const int RIGHT = 2;  // 0010
        const int BOTTOM = 4; // 0100
        const int TOP = 8;    // 1000

        Point p1 = point(0);
        p1.updateSNC(windowCenter, vup, scale);
        double x0 = p1.sncX();
        double y0 = p1.sncY();

        Point p2 = point(1);
        p2.updateSNC(windowCenter, vup, scale);
        double x1 = p2.sncX();
        double y1 = p2.sncY();

        int regionCode0 = this->regionCode(x0, y0, wmin_x, wmin_y, wmax_x, wmax_y);
        int regionCode1 = this->regionCode(x1, y1, wmin_x, wmin_y, wmax_x, wmax_y);

        bool accept = false;

        while (true) {

            if (!(regionCode0 | regionCode1)) { // totalmente dentro
                accept = true;
                break;
            } else if (regionCode0 & regionCode1) { // totalmente fora
                break;
            } else {

                // parcialmente
                double x, y;

                // At least one endpoint is outside the clip rectangle; pick it.
                int regionCodeOut = regionCode0 ? regionCode0 : regionCode1;

                // Now find the intersection point;
                // use formulas y = y0 + slope * (x - x0), x = x0 + (1 / slope) * (y - y0)
                if (regionCodeOut & TOP) {           // point is above the clip rectangle
                    x = x0 + (x1 - x0) * (wmax_y - y0) / (y1 - y0);
                    y = wmax_y;
                } else if (regionCodeOut & BOTTOM) { // point is below the clip rectangle
                    x = x0 + (x1 - x0) * (wmin_y - y0) / (y1 - y0);
                    y = wmin_y;
                } else if (regionCodeOut & RIGHT) {  // point is to the right of clip rectangle
                    y = y0 + (y1 - y0) * (wmax_x - x0) / (x1 - x0);
                    x = wmax_x;
                } else if (regionCodeOut & LEFT) {   // point is to the left of clip rectangle
                    y = y0 + (y1 - y0) * (wmin_x - x0) / (x1 - x0);
                    x = wmin_x;
                }

                // Now we move outside point to intersection point to clip
                // and get ready for next pass.
                if (regionCodeOut == regionCode0) {
                    x0 = x;
                    y0 = y;
                    regionCode0 = this->regionCode(x0, y0,  wmin_x, wmin_y, wmax_x, wmax_y);
                } else {
                    x1 = x;
                    y1 = y;
                    regionCode1 = this->regionCode(x1, y1, wmin_x, wmin_y, wmax_x, wmax_y);
                }
            }
        }

        if (accept) {
            Object* new_obj = new Object(LINE, color.r, color.g, color.b);
            new_obj->addPoint(x0, y0, 1);
            new_obj->addPoint(x1, y1, 1);
            return new_obj;
        } else {
            return 0;
        }

    } else if (shape == POLYGON) {

        Point startPoint;
        Point endPoint;

        Object* new_polygon = new Object(POLYGON, color.r ,color.g , color.b);
        
        Point* goingIn = 0;
        Point* goingOut = 0;

        for (unsigned int i = 0; i < pointsCount() - 1; i++) {

            Point p0(point(i));
            Point p1(point(i+1));

            Object* cur_line = new Object(LINE, 0, 0, 0);

            cur_line->addPoint(p0.x(), p0.y(), 1);
            cur_line->addPoint(p1.x(), p1.y(), 1);

            Object* line_clipped = cur_line->clip(wmin_x, wmin_y, wmax_x, wmax_y, windowCenter, vup, scale);

            if (line_clipped) {

                std::cout << "teve clipping" << std::endl;

                p0.updateSNC(windowCenter, vup, scale);
                p1.updateSNC(windowCenter, vup, scale);

                // tudo dentro
                if ( ((line_clipped->point(0).x() == p0.sncX()) && (line_clipped->point(0).y() == p0.sncY()) ) &&
                     ((line_clipped->point(1).x() == p1.sncX()) && (line_clipped->point(1).y() == p1.sncY()) )) {

                    std::cout << "tudo igual" << std::endl;

                    new_polygon->addPoint(p0.sncX(), p0.sncY(), 1);
                    new_polygon->addPoint(p1.sncX(), p1.sncY(), 1);

                // p_inicial dentro, saindo
                } else if ( (line_clipped->point(0).x() > -1 && line_clipped->point(0).x() < 1) &&
                            (line_clipped->point(0).y() > -1 && line_clipped->point(0).y() < 1) ) {

                    goingOut = new Point(line_clipped->point(1).x(), line_clipped->point(1).y(), 1);

                    new_polygon->addPoint(line_clipped->point(0).x(), line_clipped->point(0).y(), 1);
                    new_polygon->addPoint(line_clipped->point(1).x(), line_clipped->point(1).y(), 1);

                // p_final dentro, entrando
                } else {

                    goingIn = new Point(line_clipped->point(0).x(), line_clipped->point(0).y(), 1);

                    if (!goingOut) {
                        goingOut = goingIn;
                    }
                    if (goingIn->x() != goingOut->x()) {

                        if (goingIn->y() < goingOut->y()) {

                            if (goingIn->x() < goingOut->x()) {
                                new_polygon->addPoint(1, -1, 1);
                            } else {
                                new_polygon->addPoint(1, 1, 1);
                            }

                        } else if (goingIn->y() > goingOut->y()) {

                            if (goingIn->x() < goingOut->x()) {
                                new_polygon->addPoint(-1, -1, 1);
                            } else {
                                new_polygon->addPoint(-1, 1, 1);
                            }
                        }

                    }
                    new_polygon->addPoint(goingIn->x(), goingIn->y(), 1);

                    new_polygon->addPoint(line_clipped->point(1).x(), line_clipped->point(1).y(), 1);
                }
            } 
        }
        return new_polygon;
    }
    return 0;
}

void Object::addPoint(double x, double y, double z)
{
    Point* p = new Point(x, y, z);
    points.push_back(p);
}

unsigned int Object::pointsCount(void) const
{
    return points.size();
}

Point Object::point(int index)
{
    Point *p = points[index];
    return p->transform(transformationMatrix);
}

void Object::updateTransform(double matrix[9])
{
    //return [transformationMatrix]*[matrix]

    double *t = transformationMatrix;

    // linha 1
    double new_x1 = (t[0] * matrix[0]) + (t[1] * matrix[3]) + (t[2] * matrix[6]);
    double new_y1 = (t[0] * matrix[1]) + (t[1] * matrix[4]) + (t[2] * matrix[7]);
    double new_z1 = (t[0] * matrix[2]) + (t[1] * matrix[5]) + (t[2] * matrix[8]);

    // linha 2
    double new_x2 = (t[3] * matrix[0]) + (t[4] * matrix[3]) + (t[5] * matrix[6]);
    double new_y2 = (t[3] * matrix[1]) + (t[4] * matrix[4]) + (t[5] * matrix[7]);
    double new_z2 = (t[3] * matrix[2]) + (t[4] * matrix[5]) + (t[5] * matrix[8]);

    // linha 3
    double new_x3 = (t[6] * matrix[0]) + (t[7] * matrix[3]) + (t[8] * matrix[6]);
    double new_y3 = (t[6] * matrix[1]) + (t[7] * matrix[4]) + (t[8] * matrix[7]);
    double new_z3 = (t[6] * matrix[2]) + (t[7] * matrix[5]) + (t[8] * matrix[8]);

    t[0] = new_x1;
    t[1] = new_y1;
    t[2] = new_z1;
    t[3] = new_x2;
    t[4] = new_y2;
    t[5] = new_z2;
    t[6] = new_x3;
    t[7] = new_y3;
    t[8] = new_z3;
}

void Object::clearTransformations(void)
{
    transformationMatrix[0] = 1;
    transformationMatrix[1] = 0;
    transformationMatrix[2] = 0;
    transformationMatrix[3] = 0;
    transformationMatrix[4] = 1;
    transformationMatrix[5] = 0;
    transformationMatrix[6] = 0;
    transformationMatrix[7] = 0;
    transformationMatrix[8] = 1;
}

void Object::rotateOrigin(double a)
{
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);
}

void Object::rotateCenter(double a)
{
    Point p = getCenterPoint();
    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);

    translate(Point(p.x(), p.y()));
}

void Object::rotatePoint(double a, const Point& p)
{
    translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    updateTransform(m);

    translate(Point(p.x(), p.y()));
}

void Object::scale(const Point& vector)
{
    Point p = getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));

    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
    double m[9] = { 0 };
    m[0] = vector.x();
    m[4] = vector.y();
    m[8] = 1;

    updateTransform(m);

    this->translate(Point(p.x(), p.y()));
}

void Object::translate(const Point& displacement)
{
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = displacement.x();
    m[7] = displacement.y();
    m[8] = 1.0;
    updateTransform(m);
}

Point Object::getCenterPoint(void)
{
    double x = 0;
    double y = 0;
    unsigned int i;
    for (i=0; i < pointsCount(); i++)
    {
        x += point(i).x();
        y += point(i).y();
    }

    x = x/i;
    y = y/i;

    return Point(x, y);
}

bool Object::isFilled(void)
{
   return filled;
}

void Object::fill(bool value)
{
   filled = value;
}

Point::Point(double x, double y, double z) : wcX(x), wcY(y), wcZ(z)
{
}

Point::Point(const Point &point) : wcX(point.x()), wcY(point.y()), wcZ(point.z())
{
}

void Point::updateSNC(const Point& windowCenter, double vup, const Point& scale)
{
    //translate
    // [1  0  0
    //  0  1  0
    //  dx dy 1]
    double m[9] = { 0 };
    m[0] = 1.0;
    m[4] = 1.0;
    m[6] = windowCenter.x();
    m[7] = windowCenter.y();
    m[8] = 1.0;

    Point new_snc = transform(m);

    // rotate
    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m1[9] = { 0 };
    m1[0] = cos(-vup * PI/180.0);
    m1[1] = -sin(-vup * PI/180.0);
    m1[3] = sin(-vup * PI/180.0);
    m1[4] = cos(-vup * PI/180.0);
    m1[8] = 1.0;

    new_snc = new_snc.transform(m1);

    // scale
    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
    double m2[9] = { 0 };
    m2[0] = 2.0/scale.x();
    m2[4] = 2.0/scale.y();
    m2[8] = 1.0;

    new_snc = new_snc.transform(m2);

    snc_X = new_snc.x();
    snc_Y = new_snc.y();
    snc_Z = new_snc.z();
}

double Point::sncX(void) const
{
    return snc_X;
}

double Point::sncY(void) const
{
    return snc_Y;
}

double Point::sncZ(void) const
{
    return snc_Z;
}

double Point::x(void) const
{
    return wcX;
}

double Point::y(void) const
{
    return wcY;
}

double Point::z(void) const
{
    return wcZ;
}

void Point::x(double x)
{
    this->wcX = x;
}

void Point::y(double y)
{
    this->wcY = y;
}
void Point::z(double z)
{
    this->wcZ = z;
}

Point Point::transform(double matrix[9])
{
    //return [x y 1]*[matrix]
    double new_x = (x() * matrix[0]) + (y() * matrix[3]) + matrix[6];
    double new_y = (x() * matrix[1]) + (y() * matrix[4]) + matrix[7];
    double new_z = (x() * matrix[2]) + (y() * matrix[5]) + matrix[8];
    return Point(new_x, new_y, new_z);
}

std::string Point::toString(void) const
{
    std::stringstream s;
    s << "Point(" << x() << ","<< y() << "," << z() << ")";
    return s.str();
}

std::string Point::toObj(void) const
{
    std::stringstream s;
    s << "v " << x() << " "<< y() << " " << z() << std::endl;
    return s.str();
}
