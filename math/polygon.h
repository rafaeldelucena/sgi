#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include "math/line.h"

class Polygon
{
public:
    Polygon();
    ~Polygon();
    void addLine(const Line& line);
private:
    std::vector<Line> lines;
};

#endif // POLYGON_H
