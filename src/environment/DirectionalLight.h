#ifndef DIRECTIONALLIGHT_H_
#define DIRECTIONALLIGHT_H_

#include <glm/vec3.hpp>
#include <sstream>
#include "../util/Serializable.h"
#include "BaseLight.h"

struct DirectionalLight : public Serializable{

    DirectionalLight()
                     : direction(glm::vec3(0.0f,0.0f,0.0f))
                      {};

    DirectionalLight(std::ifstream &stream)
                     : direction(glm::vec3(0.0f,0.0f,0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing DirectionalLight" << std::endl;
    };

    virtual void serialize(std::ofstream &) override {};

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
                    if (var == "direction") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3;
                            sscanf(value.c_str(), "%f,%f,%f", &v1, &v2, &v3);
                            this->direction = glm::normalize(glm::vec3(v1, v2, v3));
                        }
                    }
                    else if (var == "[baselight]") {
                        std::cout << "here" << std::endl;
                        ret &= light.deserialize(stream);
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true & ret;
    };

    BaseLight light;
    glm::vec3 direction;

};

#endif
