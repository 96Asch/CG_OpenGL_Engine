#ifndef MATERIALCOMPONENT_H_
#define MATERIALCOMPONENT_H_

#include <string>

struct MaterialComponent : public Component {

    MaterialComponent()
                      : Component(CompType::MATERIAL),
                        source("") {};

    MaterialComponent(const std::string &source)
                      : Component(CompType::MATERIAL),
                        source(source) {};

    std::string source;

    GLuint id;

};

#endif
