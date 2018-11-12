#ifndef VELOCITYCOMPONENT_H_
#define VELOCITYCOMPONENT_H_

#include <glm/vec3.hpp>

struct VelocityComponent : public Component {

    VelocityComponent()
            : velocity(glm::vec3(0.0f)),
              speed(0.0f),
              maxSpeed(1.0f),
              acceleration(0.5f)
              {};

    VelocityComponent(const glm::vec3 &velocity,
                      const float &maxSpeed,
                      const float &acceleration)
            : velocity(velocity),
              speed(0.0f),
              maxSpeed(maxSpeed),
              acceleration(acceleration)
              {};

    glm::vec3 velocity;
    float speed, maxSpeed;
    float acceleration;
};

#endif
