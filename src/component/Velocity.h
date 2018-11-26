#ifndef VELOCITY_H_
#define VELOCITY_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Velocity : public IComponent<Velocity> {

    Velocity()
            : velocity(glm::vec3(0.0f)),
              speed(1.0f)
              {};

    Velocity(float speed)
            : velocity(glm::vec3(0.0f)),
              speed(speed)
              {};

    Velocity(std::ifstream &stream)
            : velocity(glm::vec3(0.0f)),
              speed(1.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Velocity Component" << std::endl;
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
                    if (comp == "speed")
                        if(std::getline(ss, var)) {
                            // std::cout << var << std::endl;
                            float speed = std::stof(var);
                            this->speed = speed;
                        }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 velocity;
    float speed;
};

#endif
