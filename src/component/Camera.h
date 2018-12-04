#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/vec3.hpp>
#include <sstream>
#include "Component.h"

struct Camera : public IComponent<Camera> {

    Camera() : target(glm::vec3(0.0f, 0.0f, -1.0f)),
               lastTarget(glm::vec3(0.0f)),
               up(glm::vec3(0.0f, 1.0f, 0.0f)),
               lastUp(glm::vec3(0.0f))
               {};

    Camera(std::ifstream &stream) : target(glm::vec3(0.0f, 0.0f, -1.0f)),
                                    lastTarget(glm::vec3(0.0f)),
                                    up(glm::vec3(0.0f, 1.0f, 0.0f)),
                                    lastUp(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Camera Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &) override {
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 target, lastTarget, interpolatedTarget;
    glm::vec3 up, lastUp, interpolatedUp;
    glm::vec3 right;
};

#endif
