#ifndef SCALE_H_
#define SCALE_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Scale : public IComponent<Scale> {

    Scale()
               : scale(glm::vec3(1.0f)),
                 lastScale(glm::vec3(1.0f))
                 {};

    Scale(const glm::vec3 &scale)
               : scale(scale),
                 lastScale(scale)
                 {};

    Scale(std::ifstream &stream)
               : scale(glm::vec3(1.0f)),
                 lastScale(glm::vec3(1.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Scale Component" << std::endl;
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
                    if (var == "scale") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            scale = glm::vec3(v1, v2, v3);
                            lastScale = scale;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    glm::vec3 scale, lastScale, interpolated;
};

#endif
