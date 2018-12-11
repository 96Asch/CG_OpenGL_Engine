#ifndef TERRAIN_H_
#define TERRAIN_H_

#include <glm/vec2.hpp>

#include "../factory/VaoFactory.h"
#include "../factory/ModelGenerator.h"
#include "../util/Serializable.h"

#define MAX_TEXTURES 4

struct TerrainTexture {
    std::string texture = "texture/ice.png";
    float specularPower = 0.0f, reflectance = 0.0f;

    void deserialize(std::ifstream &stream) {
        bool firstAcc(false), lastAcc(false), textureFound(false);
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
                    if (var == "texture") {
                        if(std::getline(ss, value, '=')) {
                            this->texture = value;
                            Factory::TEXTURE->createTexture(value);
                            textureFound = true;
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
                }
            }
        } while(stream && firstAcc && !lastAcc);
        if(!textureFound)
            Factory::TEXTURE->createTexture(texture);
    };
};

struct Terrain : public Serializable{

    Terrain()
            : numMaterials(0),
              hMapSource(""),
              bMapSource(""),
              size(0.0f),
              maxHeight(0.0f),
              position(glm::vec2(0.0f))
    {};

    Terrain(std::ifstream &stream)
            : numMaterials(0),
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
        bool firstAcc(false), lastAcc(false);
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
                        }
                    }
                    else if (var == "[texture]") {
                        if(numMaterials < MAX_TEXTURES) {
                            textures[numMaterials].deserialize(stream);
                            numMaterials++;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        Factory::generateTerrain(hMapSource, size, maxHeight);
        return true;
    };

    GLuint getTexture(const unsigned &index) const {
        if(index < numMaterials)
            return Factory::TEXTURE->getTexture(textures[index].texture);
        return 0;
    }


    std::shared_ptr<Vao> getVao() {
       return Factory::VAO->getVao(hMapSource);
    };

    GLuint blendMap;
    unsigned numMaterials;

    TerrainTexture textures[MAX_TEXTURES];
    std::string hMapSource;
    std::string bMapSource;
    float size;
    float maxHeight;
    glm::vec2 position;
};

#endif
