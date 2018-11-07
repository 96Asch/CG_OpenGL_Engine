#ifndef VELOCITYCOMPONENT_H_
#define VELOCITYCOMPONENT_H_

#include <glm/vec3.hpp>

struct VelocityComponent : public Component {

    VelocityComponent()
            : Component(CompType::VELOCITY), velocity(glm::vec3(0.0f)) {};

    VelocityComponent(const glm::vec3 &velocity)
            : Component(CompType::VELOCITY), velocity(velocity) {};

    glm::vec3 velocity;

};

#endif
