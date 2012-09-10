#include "view/displayfile.h"

DisplayFile::DisplayFile()
{
}

DisplayFile::~DisplayFile()
{
    lines.clear();
    points.clear();
    polygons.clear();
}

void DisplayFile::insertObject(Line *line)
{
    lines.push_back(line);
}

void DisplayFile::insertObject(Point *point)
{
    points.push_back(point);
}

void DisplayFile::insertObject(Polygon *polygon)
{
    polygons.push_back(polygon);
}
