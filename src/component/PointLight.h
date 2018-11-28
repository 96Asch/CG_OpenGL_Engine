#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include <glm/vec3.hpp>
#include <sstream>
#include "Component.h"

struct PointLight : public IComponent<PointLight>{

    PointLight()
               : color(glm::vec3(0.0f)),
                 position(glm::vec3(0.0f)),
                 lastPosition(position),
                 intensity(0.0f),
                 attenuation(glm::vec3(0.0f))
                 {};

    PointLight(const glm::vec3 &color,
               const glm::vec3 &position,
               const float &intensity,
               const glm::vec3 &attenuation)
               : color(color),
                 position(position),
                 lastPosition(position),
                 intensity(intensity),
                 attenuation(attenuation)
                 {};

    PointLight(std::ifstream &stream)
               : color(glm::vec3(1.0f)),
                 position(glm::vec3(0.0f)),
                 lastPosition(position),
                 intensity(1.0f),
                 attenuation(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing PointLight Component" << std::endl;
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
                    if (var == "color") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->color = glm::vec3(v1, v2, v3);
                        }
                    }
                    else if (var == "position") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->position = glm::vec3(v1, v2, v3);
                            this->lastPosition = this->position;
                        }
                    }
                    else if (var == "intensity") {
                        if(std::getline(ss, value, '=')) {
                            float intensity = std::stof(value);
                            this->intensity = intensity;
                        }
                    }
                    else if (var == "attenuation") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->attenuation = glm::vec3(v1, v2, v3);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};


    glm::vec3 color;
    glm::vec3 position, lastPosition;
    float intensity;
    glm::vec3 attenuation;

};

#endif
