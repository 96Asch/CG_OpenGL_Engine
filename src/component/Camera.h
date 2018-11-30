#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/vec3.hpp>
#include <sstream>
#include "Component.h"

struct Camera : public IComponent<Camera> {

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

    Camera(std::ifstream &stream) : position(glm::vec3(0.0f)),
                                    lastPosition(glm::vec3(0.0f)),
                                    target(glm::vec3(0.0f, 0.0f, -1.0f)),
                                    lastTarget(glm::vec3(0.0f)),
                                    up(glm::vec3(0.0f, 1.0f, 0.0f)),
                                    lastUp(glm::vec3(0.0f)),
                                    worldUp(glm::vec3(0.0, 1.0f, 0.0f)),
                                    right(glm::cross(target, worldUp)),
                                    yaw(0.0f),
                                    pitch(0.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Camera Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false);
        do {
            std::string buffer;
            std::string var;
            std::string value;
            stream >> std::ws;
            if(std::getline(stream, buffer)) {
                std::istringstream ss(buffer);
                if(!firstAcc && buffer == "{")
                    firstAcc = true;
                else if (firstAcc && buffer == "}")
                    lastAcc = true;
                    else if(std::getline(ss, var, '=')) {
                    if (var == "position") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->position = glm::vec3(v1, v2, v3);
                            this->lastPosition = position;
                        }
                    }
                    else if (var == "yaw") {
                        if(std::getline(ss, value, '=')) {
                            float yaw = std::stof(value);
                            this->yaw = yaw;
                        }
                    }
                    else if (var == "pitch") {
                        if(std::getline(ss, value, '=')) {
                            float pitch = std::stof(value);
                            this->pitch = pitch;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        right = glm::cross(this->target, this->worldUp);
        return true;
    };

    virtual void serialize(std::ofstream &) override {

    };

    glm::vec3 position, lastPosition;
    glm::vec3 target, lastTarget;
    glm::vec3 up, lastUp, worldUp;
    glm::vec3 right;
    float yaw, pitch;
};

#endif
