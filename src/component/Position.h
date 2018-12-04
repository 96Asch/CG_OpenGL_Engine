#ifndef POSITION_H_
#define POSITION_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Position : public IComponent<Position> {

    Position()
               : position(glm::vec3(0.0f)),
                 lastPosition(glm::vec3(0.0f))
                 {};

    Position(const glm::vec3 &position)
               : position(position),
                 lastPosition(position)
                 {};

    Position(std::ifstream &stream)
               : position(glm::vec3(0.0f)),
                 lastPosition(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Position Component" << std::endl;
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
                            lastPosition = position;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 position, lastPosition, interpolated;
};

#endif
