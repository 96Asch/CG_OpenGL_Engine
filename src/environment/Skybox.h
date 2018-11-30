#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "../util/Serializable.h"
#include "../graphic/globjects/Vao.h"
#include "../factory/VaoFactory.h"
#include "../factory/ModelLoader.h"
#include "../factory/TextureFactory.h"

#define CUBEMODEL "models/cube.obj"

struct Skybox : public Serializable {

    Skybox()
            : FACES(6),
              rotation(0.0f),
              active(false),
              size(400.0f),
              rotationSpeed(0.5f),
              source("")
    {
        // Factory::loadOBJ(CUBEMODEL,size);
    };

    Skybox(std::ifstream &stream)
            : FACES(6),
              rotation(0.0f),
              active(false),
              size(400.0f),
              rotationSpeed(0.5f),
              source("")
    {

        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Skybox" << std::endl;
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
                    if (var == "size") {
                        if(std::getline(ss, value, '=')) {
                            this->size = std::stof(value);
                        }
                    }
                    else if (var == "rotationSpeed") {
                        if(std::getline(ss, value, '=')) {
                            this->rotationSpeed = std::stof(value);
                        }
                    }
                    else if (var == "source") {
                        if(std::getline(ss, value, '=')) {
                            this->source = value;
                        }
                    }
                    else if (var == "ext") {
                        if(std::getline(ss, value, '=')) {
                            this->ext = value;
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        if(!source.empty() && !ext.empty()) {
            std::vector<std::string> files;
            for(unsigned i = 1; i <= FACES; i++) {
                files.push_back(source + '_' + std::to_string(i) + ext);
            }
            texture = Factory::TEXTURE->createCubeMapTexture(files);
            this->active = true;
        }
        else {
            std::cerr << "ERR: incorrect skybox texture specified!" << std::endl;
        }
        Factory::loadOBJ(CUBEMODEL,size);
        return true;
    };

    std::shared_ptr<Vao> getVao() {
       return Factory::VAO->getVao(CUBEMODEL);
    };

    const unsigned FACES;
    float rotation;
    float active;
    GLuint texture;

    float size;
    float rotationSpeed;
    std::string source;
    std::string ext;

};


#endif
