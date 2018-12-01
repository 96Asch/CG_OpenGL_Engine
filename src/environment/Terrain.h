#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <glm/vec2.hpp>

#include "../factory/VaoFactory.h"
#include "../factory/ModelGenerator.h"
#include "../util/Serializable.h"
#include "../component/Material.h"

struct Terrain : public Serializable{

    Terrain()
            : active(false),
              material(Material("")),
              heightMap(""),
              size(0.0f),
              position(glm::vec2(0.0f))
    {};

    Terrain(const std::string &heightMap,
            const std::string &texture,
            const glm::vec2 &position,
            const float &size)
            : active(false),
              material(Material(texture)),
              heightMap(heightMap),
              size(size),
              position(position * size)
    {
        if(!texture.empty() && size > 0) {
            Factory::generateTerrain(heightMap, size);
            active = true;
        }
    };

    Terrain(std::ifstream &stream)
            : active(false),
              material(Material("")),
              heightMap(""),
              size(100.0f),
              position(glm::vec2(0.0f))
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Terrain" << std::endl;
    };

    virtual void serialize(std::ofstream &) override {};

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false), ret(true);
        unsigned counter(0);
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
                    if (var == "heightMap") {
                        if(std::getline(ss, value, '=')) {
                            this->heightMap = value;
                        }
                    }
                    else if (var == "size") {
                        if(std::getline(ss, value, '=')) {
                            this->size = std::stof(value);
                            counter++;
                        }
                    }
                    else if (var == "position") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2;
                            sscanf(value.c_str(), "%f,%f", &v1, &v2);
                            this->position = glm::vec2(v1, v2);
                            counter++;
                        }
                    }
                    else if (var == "[material]") {
                        ret &= material.deserialize(stream);
                        counter++;
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        if(counter == 3) {
            active = true;
            Factory::generateTerrain(heightMap, size);
        }
        return true;
    };


    std::shared_ptr<Vao> getVao() {
       return Factory::VAO->getVao(heightMap);
    };

    bool active;

    Material material;
    std::string heightMap;
    float size;
    float maxHeight, minHeight;
    glm::vec2 position;



};

#endif
