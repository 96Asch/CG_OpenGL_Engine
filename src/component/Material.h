#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <sstream>
#include <glm/vec4.hpp>

#include "Component.h"
#include "../factory/TextureFactory.h"

struct Material : public IComponent<Material> {

    Material(const std::string &source)
                    : source(source),
                      diffuse(glm::vec4(0.0f)),
                      specularPower(0.0f),
                      reflectance(0.0f),
                      hasTexture(true),
                      hasFakeLighting(false)
    {
        if(!source.empty())
            id = Factory::TEXTURE->createTexture(source);
        else
            hasTexture = false;
    };

    Material()
            : source(""),
              diffuse(glm::vec4(0.0f)),
              specularPower(0.0f),
              reflectance(0.0f),
              hasTexture(true),
              hasFakeLighting(false)
    {
        if(!source.empty())
            id = Factory::TEXTURE->createTexture(source);
        else
            hasTexture = false;
    };

    Material(std::ifstream &stream)
                    : source(""),
                      diffuse(glm::vec4(0.0f)),
                      specularPower(0.0f),
                      reflectance(0.0f),
                      hasTexture(false),
                      hasFakeLighting(false)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Material Component" << std::endl;
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
                    if (var == "source") {
                        if(std::getline(ss, value, '=')) {
                            this->source = value;
                            if(!source.empty()) {
                                this->id = Factory::TEXTURE->createTexture(source);
                                this->hasTexture = true;
                            }
                        }
                    }
                    else if (var == "diffuse") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3, v4;
                            sscanf(value.c_str(), "%f,%f,%f,%f", &v1, &v2, &v3, &v4);
                            this->diffuse = glm::vec4(v1, v2, v3, v4);
                        }
                    }
                    else if (var == "specularPower") {
                        if(std::getline(ss, value, '=')) {
                            this->specularPower = std::stof(value);
                        }
                    }
                    else if (var == "reflectance") {
                        if(std::getline(ss, value, '=')) {
                            this->reflectance = std::stof(value);

                        }
                    }
                    else if (var == "hasFakeLighting") {
                        if(std::getline(ss, value, '=')) {
                            this->hasFakeLighting = std::stoi(value);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        hasTexture = !source.empty();
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    std::string source;
    glm::vec4 diffuse;
    float specularPower;
    float reflectance;
    bool hasTexture;
    bool hasFakeLighting;

    GLuint id;
};

#endif
