#ifndef MATERIALCOMPONENT_H_
#define MATERIALCOMPONENT_H_

#include <string>

struct MaterialComponent : public Component {

    MaterialComponent(const std::string &source)
                      : source(source) {};

    std::string source;

    GLuint id;

};

#endif
