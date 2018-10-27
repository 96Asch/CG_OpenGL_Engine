#ifndef MATERIALCOMPONENT_H_
#define MATERIALCOMPONENT_H_

#include <string>

struct MaterialComponent : public Component {

    std::string source;

    GLuint textureId;

};

#endif
