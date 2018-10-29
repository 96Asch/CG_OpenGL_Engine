#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>

enum CompType {
    MATERIAL,
    MODEL,
    TRANSFORM
};

struct Component {

    Component(const CompType &type) : type(type), isActive(true) {};

    CompType type;
    bool isActive;

};

#endif
