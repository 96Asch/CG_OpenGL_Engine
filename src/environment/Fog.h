#ifndef FOG_H_
#define FOG_H_

#include "../util/Serializable.h"

struct Fog : public Serializable{

    Fog() : active(false),
            color(glm::vec3(0.0f)),
            density(0.0f),
            gradient(0.0f)
    {};

    Fog(std::ifstream &stream) : active(false),
            color(glm::vec3(0.0f)),
            density(0.0f),
            gradient(0.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Fog" << std::endl;
    };

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
                    else if (var == "density") {
                        if(std::getline(ss, value, '=')) {
                            float density = std::stof(value);
                            this->density = density;
                        }
                    }
                    else if (var == "gradient") {
                        if(std::getline(ss, value, '=')) {
                            float gradient = std::stof(value);
                            this->gradient = gradient;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        if(density > 0.0f)
            active = true;
        return true;
    };

    bool active;
    glm::vec3 color;
    float density;
    float gradient;
};

#endif
