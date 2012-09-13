#ifndef OBJECT_H
#define OBJECT_H

#include <QString>

enum Shape { POINT, LINE, POLYGON };

class Object {
public:
    Object(Shape type, QString name);
    ~Object(void);
    Shape type(void) const;
    QString name(void) const;

private:
    Shape shape;
    QString objectName;
};

#endif // OBJECT_H
