#ifndef INPUTCOMPONENT_H_
#define INPUTCOMPONENT_H_

enum Action {
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 1u << 1,
    MOVE_LEFT = 1u << 2,
    MOVE_RIGHT = 1u << 3,
    MOVE_UP = 1u << 4,
    MOVE_DOWN = 1u << 5
};

struct InputComponent : public Component {

    InputComponent() : Component(CompType::INPUT), action(0) {};

    void addAction(const Action &action) {
        this->action |= action;
    };

    unsigned long action;

};

#endif
