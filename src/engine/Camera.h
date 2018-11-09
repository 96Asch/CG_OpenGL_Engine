#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/vec3.hpp>

#include "Components.h"

struct Camera {

    Camera() : position(glm::vec3(0.0f)),
               lastPosition(glm::vec3(0.0f)),
               target(glm::vec3(0.0f, 0.0f, -1.0f)),
               lastTarget(glm::vec3(0.0f)),
               up(glm::vec3(0.0f, 1.0f, 0.0f)),
               lastUp(glm::vec3(0.0f)),
               worldUp(glm::vec3(0.0, 1.0f, 0.0f)),
               right(glm::cross(target, worldUp)),
               yaw(0.0f),
               pitch(0.0f)
               {};

    ActionComponent action;
    VelocityComponent velocity;
    MouseComponent mouse;

    glm::vec3 position, lastPosition;
    glm::vec3 target, lastTarget;
    glm::vec3 up, lastUp, worldUp;
    glm::vec3 right;

    float yaw, pitch;
};

#endif
