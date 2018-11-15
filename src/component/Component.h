#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <iostream>
#include "Global.h"

struct Component {

    uint64_t owner;
    bool isActive;

    bool operator==(const Component &rhs) {
        return (rhs.owner == this->owner);
    };

    static size_t bitCounter;

};

template <class Derived>
struct InterComponent : public Component {
    static size_t bit();
};

template <class Derived>
size_t InterComponent<Derived>::bit() {
    static size_t bit = bitCounter++;
    if(bit > Global::NUM_BITS) {
        std::cerr << "Number of components exceeded: " << Global::NUM_BITS << std::endl;
        exit(-1);
    }
    return bit;
};

#endif
