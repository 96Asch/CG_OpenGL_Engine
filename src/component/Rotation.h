#ifndef ROTATION_H_
#define ROTATION_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Rotation : public IComponent<Rotation> {

    Rotation()
               : rotation(glm::vec3(0.0f)),
                 lastRotation(glm::vec3(0.0f))
                 {};

    Rotation(const glm::vec3 &rotation)
               : rotation(rotation),
                 lastRotation(rotation)
                 {};

    Rotation(std::ifstream &stream)
               : rotation(glm::vec3(0.0f)),
                 lastRotation(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Rotation Component" << std::endl;
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
                    if (var == "rotation") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            rotation = glm::vec3(v1, v2, v3);
                            lastRotation = rotation;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 rotation, lastRotation, interpolated;
};

#endif
