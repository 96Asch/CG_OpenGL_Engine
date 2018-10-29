#ifndef MODELCOMPONENT_H_
#define MODELCOMPONENT_H_

#include "Component.h"
#include "../graphic/globjects/Vao.h"

struct ModelComponent : public Component {

    ModelComponent(const std::string &source) : Component(CompType::MODEL),
                                                source(source) {};

    std::string source;

    Vao* vao;

};

#endif
