#include "view/displayfile.h"

DisplayFile::DisplayFile(void)
{
}

DisplayFile::~DisplayFile()
{
    destroyObjects();
    worldObjects.clear();
}

void DisplayFile::destroyObjects(void)
{
    unsigned int i;
    for (i=0; i < worldObjects.size(); i++)
    {
        removeObjectAt(i);
    }
}
void DisplayFile::insertObject(Object *object, QString name)
{
    worldObjects.push_back(object);
}

void DisplayFile::removeObjectAt(unsigned int index)
{
    delete worldObjects[index];
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
