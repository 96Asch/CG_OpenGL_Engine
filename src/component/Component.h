#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

enum ComponentMask {
    ACTION      = 1,
    MATERIAL    = 1u << 1,
    MODEL       = 1u << 2,
    MOUSE       = 1u << 3,
    TRANSFORM   = 1u << 4,
    VELOCITY    = 1u << 5
};

struct Component {

    Component() : isActive(true) {};

    ComponentMask mask;
    uint64_t owner;
    bool isActive;

    bool operator==(const Component &rhs) {
        return (rhs.mask == this->mask && rhs.owner == this->owner);
    };

};

#endif
