#ifndef ACTION_H_
#define ACTION_H_

#include "Component.h"
#include <bitset>

#define ACTION_BITS 16

enum ActType {
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 2,
    MOVE_LEFT = 3,
    MOVE_RIGHT = 4,
    MOVE_UP = 5,
    MOVE_DOWN = 6,
    ROTATE_LEFT = 7,
    ROTATE_RIGHT = 8,
    ROTATE_UP = 9,
    ROTATE_DOWN = 10
};

struct Action : public IComponent<Action> {

    Action() : action(0) {};

    Action(std::ifstream &stream) : action(0) {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Action Component" << std::endl;
    };

    void addAction(const ActType &action) {
        this->action.set(action);
    };

    virtual bool deserialize(std::ifstream &) override {
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    std::bitset<ACTION_BITS> action;
};

#endif
