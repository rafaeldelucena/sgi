#ifndef OBJECT_H
#define OBJECT_H

#include <string>

enum Shape { POINT, LINE, POLYGON };

class Object {
public:
    Object(Shape type);
    ~Object(void);
    Shape type(void) const;
    std::string name(void) const;

    void nominate(const std::string& str);

private:
    Shape shape;
    std::string objectName;
};

#endif // OBJECT_H
