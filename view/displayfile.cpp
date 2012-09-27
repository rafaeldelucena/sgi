#include "view/displayfile.h"

DisplayFile::DisplayFile(void)
{
}

DisplayFile::~DisplayFile()
{
    worldObjects.clear();
}

void DisplayFile::insertObject(Object *object, QString name)
{
    worldObjects.push_back(object);
}

void DisplayFile::removeObjectAt(unsigned int index)
{
    toDestroy.push_back(worldObjects[index]);
    worldObjects.erase(worldObjects.begin() + index);
}

Object* DisplayFile::getObjectAt(unsigned int index)
{
    return worldObjects[index];
}

unsigned int DisplayFile::objectsSize(void)
{
    return worldObjects.size();
}

void DisplayFile::update(void)
{
    toDestroy.clear();
}
