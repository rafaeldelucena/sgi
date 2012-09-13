#include "math/object.h"

Object::Object(Shape type, QString name)
    : objectName(name)
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

QString Object::name(void) const
{
    return objectName;
}
