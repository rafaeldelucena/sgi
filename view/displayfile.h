#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <vector>

#include "app/formas.h"

typedef std::vector<Point> PointsRef;
typedef std::vector<Line> LinesRef;
typedef std::vector<Polygon> PolygonsRef;


class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    void insertObject(const Point &point);
    void insertObject(const Line &line);
    void insertObject(const Polygon &polygon);
private:
    PointsRef points;
    LinesRef lines;
    PolygonsRef polygons;
};

#endif // DISPLAYFILE_H
