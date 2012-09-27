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
    unsigned int objectsSize();
    void update();
    void insertObject(Object *, QString);
    void removeObjectAt(unsigned int index);
    Object* getObjectAt(unsigned int index);
private:
    void destroyObjects(void);

    Objects worldObjects;
    Objects toDestroy;
};

#endif // DISPLAYFILE_H
