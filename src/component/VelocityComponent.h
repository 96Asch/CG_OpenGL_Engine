#ifndef VELOCITYCOMPONENT_H_
#define VELOCITYCOMPONENT_H_

#include <glm/vec3.hpp>

struct VelocityComponent : public Component {

    VelocityComponent()
            : Component(CompType::VELOCITY),
              velocity(glm::vec3(0.0f)),
              speed(1.0f)
              {};

    VelocityComponent(const glm::vec3 &velocity, const float &speed)
            : Component(CompType::VELOCITY),
              velocity(velocity),
              speed(speed)
              {};

    glm::vec3 velocity;
    float speed;

};

#endif
