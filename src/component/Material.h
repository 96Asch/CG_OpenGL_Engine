#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <string>
#include <sstream>
#include "Component.h"
#include "../factory/TextureFactory.h"

struct Material : public IComponent<Material> {

    Material(const std::string &source)
                      : source(source),
                        id(Factory::TEXTURE->createTexture(source)) {};

    Material(std::ifstream &stream) {
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
                    if (var == "source")
                        if(std::getline(ss, value, '=')) {
                            this->source = value;
                            this->id = Factory::TEXTURE->createTexture(source);
                        }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {

    };

    std::string source;

    GLuint id;
};

#endif
