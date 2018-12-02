#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <glm/vec2.hpp>

#include "../factory/VaoFactory.h"
#include "../factory/ModelGenerator.h"
#include "../util/Serializable.h"
#include "../component/Material.h"

#define MAX_TEXTURES 4

struct Terrain : public Serializable{

    Terrain()
            : active(false),
              numMaterials(0),
              hMapSource(""),
              bMapSource(""),
              size(0.0f),
              maxHeight(0.0f),
              position(glm::vec2(0.0f))
    {};

    Terrain(const std::string &hMapSource,
            const std::string &blendMap,
            const std::vector<std::string> &textures,
            const glm::vec2 &position,
            const float &size,
            const float &maxHeight)
            : active(false),
              numMaterials(textures.size()),
              hMapSource(hMapSource),
              bMapSource(blendMap),
              size(size),
              position(position * size)
    {
        if(size > 0) {
            Factory::generateTerrain(hMapSource, size, maxHeight);
            active = true;
        }
        for(unsigned i = 0; i < numMaterials; ++i)
            materials[i] = Material(textures.at(i));
    };

    Terrain(std::ifstream &stream)
            : active(false),
              numMaterials(0),
              hMapSource(""),
              bMapSource(""),
              size(100.0f),
              maxHeight(0.0f),
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
                            this->hMapSource = value;
                        }
                    }
                    else if (var == "blendMap") {
                        if(std::getline(ss, value, '=')) {
                            this->bMapSource = value;
                            blendMap = Factory::TEXTURE->createTexture(bMapSource);
                            counter++;
                        }
                    }
                    else if (var == "size") {
                        if(std::getline(ss, value, '=')) {
                            this->size = std::stof(value);
                            counter++;
                        }
                    }
                    else if (var == "maxHeight") {
                        if(std::getline(ss, value, '=')) {
                            this->maxHeight = std::stof(value);
                        }
                    }
                    else if (var == "position") {
                        if(std::getline(ss, value, '=')) {
                            float v1, v2;
                            sscanf(value.c_str(), "%f,%f", &v1, &v2);
                            this->position = glm::vec2(v1, v2);
                            this->position *= size;
                            counter++;
                        }
                    }
                    else if (var == "[material]") {
                        if(numMaterials < MAX_TEXTURES) {
                            ret &= materials[numMaterials].deserialize(stream);
                            numMaterials++;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        if(counter == 3) {
            active = true;
            Factory::generateTerrain(hMapSource, size, maxHeight);
        }
        return true & ret;
    };


    std::shared_ptr<Vao> getVao() {
       return Factory::VAO->getVao(hMapSource);
    };

    bool active;
    GLuint blendMap;
    unsigned numMaterials;

    Material materials[4];
    std::string hMapSource;
    std::string bMapSource;
    float size;
    float maxHeight;
    glm::vec2 position;
};

#endif
