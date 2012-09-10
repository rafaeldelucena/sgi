#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <vector>

#include "math/polygon.h"
#include "math/line.h"

class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    void insertObject(Point *point);
    void insertObject(Line *line);
    void insertObject(Polygon *polygon);
private:
    std::vector<Point*> points;
    std::vector<Line*> lines;
    std::vector<Polygon*> polygons;
};

#endif // DISPLAYFILE_H
