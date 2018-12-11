#ifndef MOUSE_H_
#define MOUSE_H_

#include "Component.h"

struct Mouse : public IComponent<Mouse> {

    Mouse() : x(0.0f), y(0.0f), dx(0.0f), dy(0.0f) {};

    Mouse(std::ifstream &stream) : x(0.0f), y(0.0f), dx(0.0f), dy(0.0f) {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Mouse Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &) override {
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    float x, y;
    float dx, dy;
};

#endif
