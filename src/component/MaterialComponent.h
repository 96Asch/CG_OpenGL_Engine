#ifndef MATERIALCOMPONENT_H_
#define MATERIALCOMPONENT_H_

#include <string>

#include "../factory/TextureFactory.h"

struct MaterialComponent : public Component {

    MaterialComponent(const std::string &source)
                      : source(source),
                        id(Factory::TEXTURE->createTexture(source)) {};

    std::string source;

    GLuint id;

};

#endif
