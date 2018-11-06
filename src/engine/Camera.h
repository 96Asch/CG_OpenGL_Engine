#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/vec3.hpp>

struct Camera {

    Camera(const glm::vec3 &position,
           const glm::vec3 &target,
           const glm::vec3 &up)
           : position(position), target(target), up(up)
           {};

    Camera()
           : position(glm::vec3(0.0f)),
             target(glm::vec3(0.0f, 0.0f, -1.0f)),
             up(glm::vec3(0.0f, 1.0f, 0.0f))
           {};

    glm::vec3 position;

    glm::vec3 target;

    glm::vec3 up;
};

#endif
