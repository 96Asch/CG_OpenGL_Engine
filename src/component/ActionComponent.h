#ifndef ACTIONCOMPONENT_H_
#define ACTIONCOMPONENT_H_

enum Action {
    MOVE_FORWARD = 1,
    MOVE_BACKWARD = 1u << 1,
    MOVE_LEFT = 1u << 2,
    MOVE_RIGHT = 1u << 3,
    MOVE_UP = 1u << 4,
    MOVE_DOWN = 1u << 5,
};

struct ActionComponent : public Component {

    ActionComponent() : Component(CompType::ACTION), action(0) {};

    void addAction(const Action &action) {
        this->action |= action;
    };

    unsigned long action;
};

#endif
