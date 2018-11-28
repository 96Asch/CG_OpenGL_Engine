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
                      ambient(glm::vec4(0.0f)),
                      diffuse(glm::vec4(0.0f)),
                      specular(glm::vec4(0.0f)),
                      reflectance(0.0f),
                      hasTexture(true),
                      hasFakeLighting(false),
                      hasNormalMap(false),
                      id(Factory::TEXTURE->createTexture(source))
                      {};

    Material(std::ifstream &stream)
                    : source(""),
                      ambient(glm::vec4(0.0f)),
                      diffuse(glm::vec4(0.0f)),
                      specular(glm::vec4(0.0f)),
                      reflectance(0.0f),
                      hasTexture(false),
                      hasFakeLighting(false),
                      hasNormalMap(false)
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
                            this->id = Factory::TEXTURE->createTexture(source);
                        }
                    }
                    else if (var == "ambient") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3, v4;
                            sscanf(value.c_str(), "%f,%f,%f,%f", &v1, &v2, &v3, &v4);
                            this->ambient = glm::vec4(v1, v2, v3, v4);
                        }
                    }
                    else if (var == "diffuse") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3, v4;
                            sscanf(value.c_str(), "%f,%f,%f,%f", &v1, &v2, &v3, &v4);
                            this->diffuse = glm::vec4(v1, v2, v3, v4);
                        }
                    }
                    else if (var == "specular") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2, v3, v4;
                            sscanf(value.c_str(), "%f,%f,%f,%f", &v1, &v2, &v3, &v4);
                            this->specular = glm::vec4(v1, v2, v3, v4);
                        }
                    }
                    else if (var == "reflectance") {
                        if(std::getline(ss, value, '=')) {
                            float reflectance = std::stof(value);
                            this->reflectance = reflectance;
                        }
                    }
                    else if (var == "hasFakeLighting") {
                        if(std::getline(ss, value, '=')) {
                            bool hasFakeLighting = std::stoi(value);
                            this->hasFakeLighting = hasFakeLighting;
                        }
                    }
                    else if (var == "hasNormalMap") {
                        if(std::getline(ss, value, '=')) {
                            bool hasNormalMap = std::stoi(value);
                            this->hasNormalMap = hasNormalMap;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        hasTexture = !source.empty();
        return true;
    };

    virtual void serialize(std::ofstream &) override {

    };

    std::string source;
    glm::vec4 ambient;
    glm::vec4 diffuse;
    glm::vec4 specular;
    float reflectance;
    bool hasTexture;
    bool hasFakeLighting;
    bool hasNormalMap;

    GLuint id;
};

#endif
