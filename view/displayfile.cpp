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
    int i;
    for (i=0; i < worldObjects.size(); i++)
    {
        delete worldObjects[i];
    }
}
#include <iostream>
void DisplayFile::insertObject(Object *object, QString name)
{
    std::cout << "entrou aqui! " << std::endl;
    if (name.size() != 0) {
        object->name(name);
    }
    std::cout << object->toString() << std::endl;
    worldObjects.push_back(object);
}

ObjectsPtr& DisplayFile::objects(void)
{
    return worldObjects;
}
