#ifndef LOOKAT_H_
#define LOOKAT_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct LookAt : public IComponent<LookAt> {

    LookAt()
               : direction(glm::vec3(0.0f)),
                 lastDirection(glm::vec3(0.0f))
                 {};

    LookAt(const glm::vec3 &direction)
               : direction(direction),
                 lastDirection(direction)
                 {};

    LookAt(std::ifstream &stream)
               : direction(glm::vec3(0.0f)),
                 lastDirection(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing direction Component" << std::endl;
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
                    if (var == "direction") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            direction = glm::vec3(v1, v2, v3);
                            lastDirection = direction;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 direction, lastDirection, interpolated;
};

#endif
