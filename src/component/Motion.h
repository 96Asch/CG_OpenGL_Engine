#ifndef MOTION_H_
#define MOTION_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Motion : public IComponent<Motion> {

    Motion()
            : direction(glm::vec3(0.0f)),
              rotation(glm::vec3(0.0f)),
              movSpeed(1.0f),
              rotSpeed(0.5f)
              {};

    Motion(const float &movSpeed, const float &rotSpeed)
            : direction(glm::vec3(0.0f)),
              rotation(glm::vec3(0.0f)),
              movSpeed(movSpeed),
              rotSpeed(rotSpeed)
              {};

    Motion(std::ifstream &stream)
            : direction(glm::vec3(0.0f)),
              rotation(glm::vec3(0.0f)),
              movSpeed(1.0f),
              rotSpeed(0.5f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Motion Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false);
        do {
            std::string buffer;
            std::string comp;
            std::string var;
            stream >> std::ws;
            if(std::getline(stream, buffer)) {
                std::istringstream ss(buffer);
                if(!firstAcc && buffer == "{")
                    firstAcc = true;
                else if (firstAcc && buffer == "}")
                    lastAcc = true;
                else if(std::getline(ss, comp, '=')) {
                    if (comp == "movSpeed") {
                        if(std::getline(ss, var)) {
                            float speed = std::stof(var);
                            this->movSpeed = speed;
                        }
                    }
                    else if (comp == "rotSpeed") {
                        if(std::getline(ss, var)) {
                            float speed = std::stof(var);
                            this->rotSpeed = speed;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 direction;
    glm::vec3 rotation;
    float movSpeed;
    float rotSpeed;
};

#endif
