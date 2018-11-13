#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

enum ComponentMask {
    NIL         = 0,
    ACTION      = 1UL,
    MATERIAL    = 1UL << 1,
    MODEL       = 1UL << 2,
    MOUSE       = 1UL << 3,
    TRANSFORM   = 1UL << 4,
    VELOCITY    = 1UL << 5
};

struct Component {

    Component() :mask(ComponentMask::NIL), isActive(true) {};

    ComponentMask mask;
    uint64_t owner;
    bool isActive;

    bool operator==(const Component &rhs) {
        return (rhs.mask == this->mask && rhs.owner == this->owner);
    };

};

#endif
