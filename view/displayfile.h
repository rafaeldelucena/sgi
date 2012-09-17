#ifndef DISPLAYFILE_H
#define DISPLAYFILE_H

#include <vector>
#include <QString>
#include "app/formas.h"

class DisplayFile
{
public:
    DisplayFile();
    ~DisplayFile();
    ObjectsPtr& objects();
    void insertObject(Object *, QString);
    void removeObjectAt(unsigned int index);
private:
    void destroyObjects(void);

    ObjectsPtr worldObjects;
};

#endif // DISPLAYFILE_H
