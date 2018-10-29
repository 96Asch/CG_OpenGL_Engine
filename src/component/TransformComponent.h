#ifndef TRANSFORMCOMPONENT_H_
#define TRANSFORMCOMPONENT_H_

#include "Component.h"
#include <glm/vec3.hpp>

struct TransformComponent : public Component {

    TransformComponent(const glm::vec3 &position,
                       const glm::vec3 &rotation,
                       const glm::vec3 &scale)
                       : Component(CompType::TRANSFORM),
                         position(position),
                         rotation(rotation),
                         scale(scale) {};

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif
