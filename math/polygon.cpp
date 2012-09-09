#include "math/polygon.h"

Polygon::Polygon()
{
}

Polygon::~Polygon()
{
    lines.clear();
}

void Polygon::addLine(const Line &line)
{
    lines.push_back(line);
}
