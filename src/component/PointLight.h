#ifndef POINTLIGHT_H_
#define POINTLIGHT_H_

#include <glm/vec3.hpp>
#include <sstream>
#include "../environment/BaseLight.h"
#include "Component.h"

struct PointLight : public IComponent<PointLight>{

    PointLight()
               : position(glm::vec3(0.0f)),
                 lastPosition(position),
                 attenuation(glm::vec3(0.0f))
                 {};

    PointLight(std::ifstream &stream)
               : position(glm::vec3(0.0f)),
                 lastPosition(position),
                 attenuation(glm::vec3(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing PointLight Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false), ret(true);
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
                    std::cout << "plight: " << var << std::endl;
                    if (var == "position") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->position = glm::vec3(v1, v2, v3);
                            this->lastPosition = this->position;
                        }
                    }
                    else if (var == "[baselight]") {
                        ret &= light.deserialize(stream);
                    }
                    else if (var == "attenuation") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->attenuation = glm::vec3(v1, v2, v3);
                            std::cout << "attenuation" << std::endl;
                        }
                    }
                    else if (var == "range") {
                        if(std::getline(ss, value, '=')) {
                            this->range = std::stof(value);
                            std::cout << "range" << std::endl;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true & ret;
    };

    virtual void serialize(std::ofstream &) override {};


    BaseLight light;
    glm::vec3 position, lastPosition;
    glm::vec3 attenuation;
    float range;

};

#endif
