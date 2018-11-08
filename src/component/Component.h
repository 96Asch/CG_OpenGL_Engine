#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>

enum CompType {
    NONE,
    MATERIAL,
    MODEL,
    TRANSFORM,
    VELOCITY,
    VIEW,
    INPUT
};

struct Component {

    Component() : type(CompType::NONE), isActive(false) {};

    Component(const CompType &type) : type(type), isActive(true) {};

    CompType type;
    bool isActive;

};

#endif
