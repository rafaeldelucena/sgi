#include "math/object.h"

Object::Object(Shape type)
    : objectName()
{
    shape = type;
}

Object::~Object(void)
{
    objectName.clear();
}

Shape Object::type(void) const
{
    return shape;
}

std::string Object::name(void) const
{
    return objectName;
}

void Object::nominate(const std::string& str)
{
    objectName = str;
}
