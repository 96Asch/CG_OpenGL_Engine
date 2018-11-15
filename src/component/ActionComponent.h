#ifndef ACTIONCOMPONENT_H_
#define ACTIONCOMPONENT_H_

#include "Component.h"
#include <bitset>

#define ACTION_BITS 16

enum Action {
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 2,
    MOVE_LEFT = 3,
    MOVE_RIGHT = 4,
    MOVE_UP = 5,
    MOVE_DOWN = 6,
};

struct ActionComponent : public InterComponent<ActionComponent> {

    ActionComponent() : action(0) {};

    void addAction(const Action &action) {
        this->action.set(action);
    };

    std::bitset<ACTION_BITS> action;
};

#endif
