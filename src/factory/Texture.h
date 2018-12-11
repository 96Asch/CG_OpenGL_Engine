#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "TextureFactory.h"


struct Texture {

    Texture() : diffuse(Factory::DEFAULT_DIFFUSE),
                specular(Factory::DEFAULT_SPECULAR)
    {};

    Texture(const std::string &diffuse,
            const std::string &specular)
            : diffuse(Factory::DEFAULT_DIFFUSE),
              specular(Factory::DEFAULT_SPECULAR)
    {
        if(Factory::TEXTURE->createTexture(diffuse))
            this->diffuse = diffuse;
        else
            Factory::TEXTURE->createTexture(Factory::DEFAULT_DIFFUSE);
        if(!Factory::TEXTURE->createTexture(specular))
            this->specular = specular;
        else
            Factory::TEXTURE->createTexture(Factory::DEFAULT_SPECULAR);
    };

    void deserialize(std::ifstream &stream) {
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
                    if (var == "diffuse") {
                        if(std::getline(ss, value, '=')) {
                            this->diffuse = value;
                            if(!Factory::TEXTURE->createTexture(value)) {
                                Factory::TEXTURE->createTexture(Factory::DEFAULT_DIFFUSE);
                                diffuse = Factory::DEFAULT_DIFFUSE;
                            }
                        }
                    }
                    if (var == "specular") {
                        if(std::getline(ss, value, '=')) {
                            this->specular = value;
                            if(!Factory::TEXTURE->createTexture(value)) {
                                Factory::TEXTURE->createTexture(Factory::DEFAULT_SPECULAR);
                                specular = Factory::DEFAULT_SPECULAR;
                            }
                        }
                    }
                }
            }
        } while(stream && firstAcc && !lastAcc);
    };

    GLuint getDiffuse() const {
        return Factory::TEXTURE->getTexture(diffuse);
    }

    GLuint getSpecular() const {
        return Factory::TEXTURE->getTexture(specular);
    }

    void loadCurrent() {
        Factory::TEXTURE->createTexture(diffuse);
        Factory::TEXTURE->createTexture(specular);
    }

    std::string diffuse;
    std::string specular;
};

#endif
