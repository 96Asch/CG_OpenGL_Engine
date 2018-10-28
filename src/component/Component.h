#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>


struct Component {

    Component(const std::string &type) : type(type), isActive(true) {};

    std::string type;
    bool isActive;

};

#endif
