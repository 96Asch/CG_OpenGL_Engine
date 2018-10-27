#ifndef MESHCOMPONENT_H_
#define MESHCOMPONENT_H_

#include "Component.h"
#include "../graphic/globjects/Vao.h"

struct MeshComponent : public Component {

    std::string source

    Vao vao;

};

#endif
