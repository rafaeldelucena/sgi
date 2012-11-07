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
    points.clear();
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
    }

    else if (shape == LINE) {

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

        bool has_some_line_inside = false;

        Object* new_polygon = new Object(POLYGON, color.r ,color.g , color.b);

        Point* goingIn = 0;
        Point* goingOut = 0;

        for (unsigned int i = 0; i < this->pointsCount() -1; i++) {

            Point p0(point(i));
            Point p1(point(i+1));

            Object cur_line(LINE);

            cur_line.addPoint(p0.x(), p0.y(), 1);
            cur_line.addPoint(p1.x(), p1.y(), 1);

            Object* line_clipped = cur_line.clip(wmin_x, wmin_y, wmax_x, wmax_y, windowCenter, vup, scale);

            p0.updateSNC(windowCenter, vup, scale);
            p1.updateSNC(windowCenter, vup, scale);

            if (line_clipped) {

                // tudo dentro
                if ( ((line_clipped->point(0).x() > -1 && line_clipped->point(0).x() < 1) &&
                     (line_clipped->point(0).y() > -1 && line_clipped->point(0).y() < 1) )
                    &&
                     ((line_clipped->point(1).x() > -1 && line_clipped->point(1).x() < 1) &&
                     (line_clipped->point(1).y() > -1 && line_clipped->point(1).y() < 1) ) ) {

                    new_polygon->addPoint(p0.sncX(), p0.sncY(), 1);
                    new_polygon->addPoint(p1.sncX(), p1.sncY(), 1);

                    has_some_line_inside = true;

                // p_inicial dentro, saindo
                } else if ( (line_clipped->point(0).x() > -1 && line_clipped->point(0).x() < 1) &&
                            (line_clipped->point(0).y() > -1 && line_clipped->point(0).y() < 1) ) {

                    goingOut = new Point(p1.x(), p1.y(), 1);

                    new_polygon->addPoint(line_clipped->point(0).x(), line_clipped->point(0).y(), 1);
                    new_polygon->addPoint(line_clipped->point(1).x(), line_clipped->point(1).y(), 1);

                    has_some_line_inside = true;

                // p_final dentro, entrando
                } else {

                    goingIn = new Point(p1.x(), p1.y(), 1);

                    if (!goingOut) {

                        goingOut = goingIn;

                    } else {

                        double new_x = 0;
                        double new_y = 0;

                        if (goingOut->sncX() >= 1) {
                            new_x = 1;
                        } else if (goingOut->sncX() <= -1){
                            new_x = -1;
                        }

                        if (goingOut->sncY() >= 1) {
                            new_y = 1;
                        } else if (goingOut->sncY() <= -1) {
                            new_y = -1;
                        }

                        if (new_x != 0  && new_y != 0 ) {
                            new_polygon->addPoint(new_x, new_y, 1);
                        }
                    }

                    new_polygon->addPoint(line_clipped->point(0).x(), line_clipped->point(0).y(), 1);
                    new_polygon->addPoint(line_clipped->point(1).x(), line_clipped->point(1).y(), 1);
                }
                delete line_clipped;
                line_clipped = 0;

            } else {

                double new_x;
                double new_y;
                Point p;

                if (!goingOut || i == 0 || i == this->pointsCount() - 1) {
                    p = p0;
                } else if (goingOut) {
                    p = p1;
                }

                if (p.sncX() >= 1) {
                    new_x = 1;
                } else if (p.sncX() <= -1) {
                    new_x = -1;
                } else {
                    new_x = p.sncX();
                }
                if (p.sncY() >= 1) {
                    new_y = 1;
                } else if (p.sncY() <= -1) {
                    new_y = -1;
                } else {
                    new_y = p.sncY();
                }

                new_polygon->addPoint(new_x, new_y, 1);
            }
        }
        if (has_some_line_inside) {
            return new_polygon;
        }
        if (goingOut) {
            delete goingOut;
            goingOut = 0;
        }

        if (goingIn) {
            delete goingIn;
            goingIn = 0;
        }
    }
    return 0;
}

void Object::addPoint(double x, double y, double z)
{
    Point* p = new Point(x, y, z);
    this->points.push_back(p);
}

unsigned int Object::pointsCount(void) const
{
    return this->points.size();
}

Point Object::point(int index)
{
    Point *p = this->points[index];
    return p->transform(transformationMatrix);
}

void Object::updateTransform(double matrix[9])
{
    //return [transformationMatrix]*[matrix]

    double *t = this->transformationMatrix;

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
    this->transformationMatrix[0] = 1;
    this->transformationMatrix[1] = 0;
    this->transformationMatrix[2] = 0;
    this->transformationMatrix[3] = 0;
    this->transformationMatrix[4] = 1;
    this->transformationMatrix[5] = 0;
    this->transformationMatrix[6] = 0;
    this->transformationMatrix[7] = 0;
    this->transformationMatrix[8] = 1;
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
    this->updateTransform(m);
}

void Object::rotateCenter(double a)
{
    Point p = this->getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    this->updateTransform(m);

    this->translate(Point(p.x(), p.y()));
}

void Object::rotatePoint(double a, const Point& p)
{
    this->translate(Point(-p.x(), -p.y()));

    // [cos(a) -sin(a) 0
    //  sin(a)  cos(a) 0
    //    0       0    1]
    double m[9] = { 0 };
    m[0] = cos(a * PI/180.0);
    m[1] = -sin(a * PI/180.0);
    m[3] = sin(a * PI/180.0);
    m[4] = cos(a * PI/180.0);
    m[8] = 1.0;
    this->updateTransform(m);

    this->translate(Point(p.x(), p.y()));
}

void Object::scale(const Point& vector)
{
    Point p = this->getCenterPoint();
    this->translate(Point(-p.x(), -p.y()));

    // [Sx 0  0
    //  0  Sy 0
    //  0  0  1]
    double m[9] = { 0 };
    m[0] = vector.x();
    m[4] = vector.y();
    m[8] = 1;

    this->updateTransform(m);

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
   this-> updateTransform(m);
}

Point Object::getCenterPoint(void)
{
    double x = 0;
    double y = 0;
    unsigned int i;
    for (i=0; i < this->pointsCount(); i++)
    {
        x += this->point(i).x();
        y += this->point(i).y();
    }

    x = x/i;
    y = y/i;

    return Point(x, y);
}

bool Object::isFilled(void)
{
   return this->filled;
}

void Object::fill(bool value)
{
   this->filled = value;
}

Point::Point(double x, double y, double z) : wcX(x), wcY(y), wcZ(z)
{
}

Point::Point(const Point &point) : wcX(point.x()), wcY(point.y()), wcZ(point.z())
{
}

Point Point::updateSNC(const Point& windowCenter, double vup, const Point& scale)
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

    return Point(snc_X, snc_Y, snc_Z);
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

double * BezierDerived(const Point& p1, const Point& p2, const Point & p3, const Point & p4 , double t)
{
    double bezier[16];
    bezier[0] = 1.0;
    bezier[1] = 0;
    bezier[2] = 0;
    bezier[3] = 0;
    bezier[4] = 0;
    bezier[5] = 0;
    bezier[6] = 0;
    bezier[7] = 1.0;
    bezier[8] = -3.0;
    bezier[9] = 3.0;
    bezier[10] = 0;
    bezier[11] = 0;
    bezier[12] = 0;
    bezier[13] = 0;
    bezier[14] = -3.0;
    bezier[15] = 3.0;

    std::cout << "bezier: " << "0: " << bezier[0] << "| 1: " << bezier[1] << "| 2: " << bezier[2] << "| 3: " << bezier[3] <<  std::endl;
    std::cout << "bezier: " << "4: " << bezier[4] << "| 5: " << bezier[5] << "| 6: " << bezier[6] << "| 7: " << bezier[7] <<  std::endl;
    std::cout << "bezier: " << "8: " << bezier[8] << "| 9: " << bezier[9] << "| 10: " << bezier[10] << "| 11: " << bezier[11] <<  std::endl;
    std::cout << "bezier: " << "12: " << bezier[12] << "| 13: " << bezier[13] << "| 14: " << bezier[14] << "| 15: " << bezier[15] <<  std::endl;

    double xA = bezier[0] * p1.x() + bezier[1] * p2.x() + bezier[2] * p3.x() + bezier[3] * p4.x();
    double xB = bezier[4] * p1.x() + bezier[5] * p2.x() + bezier[6] * p3.x() + bezier[7] * p4.x();
    double xC = bezier[8] * p1.x() + bezier[9] * p2.x() + bezier[10] * p3.x() + bezier[11] * p4.x();
    double xD = bezier[12] * p1.x() + bezier[13] * p2.x() + bezier[14] * p3.x() + bezier[15] * p4.x();

    double yA = bezier[0] * p1.y() + bezier[1] * p2.y() + bezier[2] * p3.y() + bezier[3] * p4.y();
    double yB = bezier[4] * p1.y() + bezier[5] * p2.y() + bezier[6] * p3.y() + bezier[7] * p4.y();
    double yC = bezier[8] * p1.y() + bezier[9] * p2.y() + bezier[10] * p3.y() + bezier[11] * p4.y();
    double yD = bezier[12] * p1.y() + bezier[13] * p2.y() + bezier[14] * p3.y() + bezier[15] * p4.y();


    double * pontos = new double[8];
    pontos[0] = xA;
    pontos[1] = yA;
    pontos[2] = xB;
    pontos[3] = yB;
    pontos[4] = xC;
    pontos[5] = yC;
    pontos[6] = xD;
    pontos[7] = yD;
    return pontos;		

}

double * BSplineDerived(const Point& p1, const Point& p2, const Point & p3, const Point & p4 , double t)
{
    double bspline[16];
    bspline[0] = -1.0/6.0;
    bspline[1] = 0.5;
    bspline[2] = -0.5;
    bspline[3] = 1.0/6.0;
    bspline[4] = 0.5;
    bspline[5] = -1;
    bspline[6] = 0.5;
    bspline[7] = 0.0;
    bspline[8] = -0.5;
    bspline[9] = 0.0;
    bspline[10] = 0.5;
    bspline[11] = 0;
    bspline[12] = 1.0/6.0;
    bspline[13] = 2.0/3.0;
    bspline[14] = 1.0/6.0;
    bspline[15] = 0.0;

    std::cout << "bspline: " << "0: " << bspline[0] << "| 1: " << bspline[1] << "| 2: " << bspline[2] << "| 3: " << bspline[3] <<  std::endl;
    std::cout << "bspline: " << "4: " << bspline[4] << "| 5: " << bspline[5] << "| 6: " << bspline[6] << "| 7: " << bspline[7] <<  std::endl;
    std::cout << "bspline: " << "8: " << bspline[8] << "| 9: " << bspline[9] << "| 10: " << bspline[10] << "| 11: " << bspline[11] <<  std::endl;
    std::cout << "bspline: " << "12: " << bspline[12] << "| 13: " << bspline[13] << "| 14: " << bspline[14] << "| 15: " << bspline[15] <<  std::endl;

    double xA = bspline[0] * p1.x() + bspline[1] * p2.x() + bspline[2] * p3.x() + bspline[3] * p4.x();
    double xB = bspline[4] * p1.x() + bspline[5] * p2.x() + bspline[6] * p3.x() + bspline[7] * p4.x();
    double xC = bspline[8] * p1.x() + bspline[9] * p2.x() + bspline[10] * p3.x() + bspline[11] * p4.x();
    double xD = bspline[12] * p1.x() + bspline[13] * p2.x() + bspline[14] * p3.x() + bspline[15] * p4.x();

    double yA = bspline[0] * p1.y() + bspline[1] * p2.y() + bspline[2] * p3.y() + bspline[3] * p4.y();
    double yB = bspline[4] * p1.y() + bspline[5] * p2.y() + bspline[6] * p3.y() + bspline[7] * p4.y();
    double yC = bspline[8] * p1.y() + bspline[9] * p2.y() + bspline[10] * p3.y() + bspline[11] * p4.y();
    double yD = bspline[12] * p1.y() + bspline[13] * p2.y() + bspline[14] * p3.y() + bspline[15] * p4.y();

    std::cout << "Pontos: " << "p1x: " << p1.x() << " p1y: " << p1.y() << " p2x: " << p2.x() << " p2y: " << p2.y() << " p3x: " << p3.x() << " p3y: " << p3.y() << " p4x: " << p4.x() << " p4y: " << p4.y() <<  std::endl;
    std::cout << "Coeficientes: " << "xA: " << xA << " xB: " << xB << " xC: " << xC << " xD: " << xD << " yA: " << yA << " yB: " << yB << " yC: " << yC << " yD: " << yD <<  std::endl;

    double t2 = t*t;
    double t3 = t2*t;

    double E[16];
    E[0] = 0;
    E[1] = 0;
    E[2] = 0;
    E[3] = 1;
    E[4] = t3;
    E[5] = t2;
    E[6] = t;
    E[7] = 0;
    E[8] = 6*t3;
    E[9] = 2*t2;
    E[10] = 0;
    E[11] = 0;
    E[12] = 6*t3;
    E[13] = 0;
    E[14] = 0;
    E[15] = 0;

    std::cout << "E: " << "0: " << E[0] << "| 1: " << E[1] << "| 2: " << E[2] << "| 3: " << E[3] <<  std::endl;
    std::cout << "E: " << "4: " << E[4] << "| 5: " << E[5] << "| 6: " << E[6] << "| 7: " << E[7] <<  std::endl;
    std::cout << "E: " << "8: " << E[8] << "| 9: " << E[9] << "| 10: " << E[10] << "| 11: " << E[11] <<  std::endl;
    std::cout << "E: " << "12: " << E[12] << "| 13: " << E[13] << "| 14: " << E[14] << "| 15: " << E[15] <<  std::endl;

    double x =   E[0] * xA + E[1] * xB + E[2] * xC + E[3] * xD;
    double dx =  E[4] * xA + E[5] * xB + E[6] * xC + E[7] * xD;
    double d2x = E[8] * xA + E[9] * xB + E[10] * xC + E[11] * xD;
    double d3x = E[12] * xA + E[13] * xB + E[14] * xC + E[15] * xD;

    double y =   E[0] * yA + E[1] * yB + E[2] * yC + E[3] * yD;
    double dy =  E[4] * yA + E[5] * yB + E[6] * yC + E[7] * yD;
    double d2y = E[8] * yA + E[9] * yB + E[10] * yC + E[11] * yD;
    double d3y = E[12] * yA + E[13] * yB + E[14] * yC + E[15] * yD;

    double * pontos = new double[8];
    pontos[0] = x;
    pontos[1] = y;
    pontos[2] = dx;
    pontos[3] = dy;
    pontos[4] = d2x;
    pontos[5] = d2y;
    pontos[6] = d3x;
    pontos[7] = d3y;
    return pontos;		
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
