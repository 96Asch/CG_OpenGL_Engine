#ifndef MOUSECOMPONENT_H_
#define MOUSECOMPONENT_H_

#include "Component.h"

struct MouseComponent : public InterComponent<MouseComponent> {

    MouseComponent() : x(0.0f), y(0.0f),
                       dx(0.0f), dy(0.0f) {};

    float x, y;
    float dx, dy;

};

#endif
