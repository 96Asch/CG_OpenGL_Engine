#ifndef VELOCITYCOMPONENT_H_
#define VELOCITYCOMPONENT_H_

#include "Component.h"

#include <glm/vec3.hpp>

struct VelocityComponent : public InterComponent<VelocityComponent> {

    VelocityComponent()
            : velocity(glm::vec3(0.0f)),
              speed(1.0f)
              {};

    VelocityComponent(float speed)
            : velocity(glm::vec3(0.0f)),
              speed(speed)
              {};

    glm::vec3 velocity;
    float speed;
};

#endif
