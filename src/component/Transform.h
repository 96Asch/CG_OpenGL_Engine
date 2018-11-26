#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Transform : public IComponent<Transform> {

    Transform()
               : position(glm::vec3(0.0f)),
                 rotation(glm::vec3(0.0f)),
                 scale(glm::vec3(1.0f)) {};

    Transform(const glm::vec3 &position,
              const glm::vec3 &rotation,
              const glm::vec3 &scale)
               : position(position),
                 rotation(rotation),
                 scale(scale) {};

    Transform(std::ifstream &stream) {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Transform Component" << std::endl;
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
                            position = glm::vec3(v1, v2, v3);
                        }
                    }
                    else if (var == "rotation") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            rotation = glm::vec3(v1, v2, v3);
                        }
                    }
                    else if (var == "scale") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            scale = glm::vec3(v1, v2, v3);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif
