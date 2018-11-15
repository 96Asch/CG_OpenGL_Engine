#ifndef MODELCOMPONENT_H_
#define MODELCOMPONENT_H_

#include "Component.h"
#include "../graphic/globjects/Vao.h"
#include "../factory/ModelLoader.h"

struct ModelComponent : public InterComponent<ModelComponent> {

    ModelComponent(const std::string &source)
                   : source(source), vao(Factory::loadOBJ(source)) {};

    std::string source;

    Vao* vao;

};

#endif
