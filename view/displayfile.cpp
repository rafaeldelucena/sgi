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
    if (name.size() != 0) {
        object->name(name);
    }
    worldObjects.push_back(object);
}

void DisplayFile::removeObjectAt(unsigned int index)
{
    delete worldObjects[index];
    worldObjects.erase(worldObjects.begin() + index);
}

ObjectsPtr& DisplayFile::objects(void)
{
    return worldObjects;
}
