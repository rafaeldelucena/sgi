#include "math/displayfile.h"

DisplayFile::DisplayFile()
{
}

DisplayFile::~DisplayFile()
{
    lines.clear();
    points.clear();
    polygons.clear();
}

void DisplayFile::insertLine(Line *line)
{
    lines.push_back(line);
}

void DisplayFile::insertPoint(Point *point)
{
    points.push_back(point);
}

void DisplayFile::insertPolygon(Polygon *polygon)
{
    polygons.push_back(polygon);
}
