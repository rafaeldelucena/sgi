#include "view/displayfile.h"

#include <iostream>

DisplayFile::DisplayFile()
{
}

DisplayFile::~DisplayFile()
{
    lines.clear();
    points.clear();
    polygons.clear();
}

void DisplayFile::insertObject(const Line &line)
{
    lines.push_back(line);
}

void DisplayFile::insertObject(const Point &point)
{
    points.push_back(point);
}

void DisplayFile::insertObject(const Polygon &polygon)
{
    polygons.push_back(polygon);
}
