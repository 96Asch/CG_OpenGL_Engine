#ifndef BASELIGHT_H_
#define BASELIGHT_H_

#include "../util/Serializable.h"
#include <sstream>
#include <glm/vec3.hpp>

struct BaseLight : public Serializable{


    BaseLight() {};

    BaseLight(std::ifstream &stream) : color(glm::vec3(0)),
                                       intensity(0.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing BaseLight" << std::endl;
    }

    virtual void serialize(std::ofstream &) override {};

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
                    else if (var == "intensity") {
                        if(std::getline(ss, value, '=')) {
                            float intensity = std::stof(value);
                            this->intensity = intensity;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    glm::vec3 color;
    float intensity;


};

#endif
