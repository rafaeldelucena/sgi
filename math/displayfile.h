#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <vector>

#include "math/polygon.h"

class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    void insertPoint(Point* point);
    void insertLine(Line* line);
    void insertPolygon(Polygon* polygon);
private:
    std::vector<Point*> points;
    std::vector<Line*> lines;
    std::vector<Polygon*> polygons;
};

#endif // DISPLAYFILE_H
