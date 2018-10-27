#ifndef UNIFORMFLOAT_H_
#define UNIFORMFLOAT_H_

#include "Global.h"
#include "Uniform.h"

struct UniformFloat : public Uniform {

    GLfloat current;
    bool isCurrent;

    UniformFloat(const std::string &name) : Uniform(name),
                                            current(0.0f),
                                            isCurrent(true)  {};

    void load(const GLfloat &value) {
        if(!isCurrent || current != value) {
            glUniform1f(location, value);
            isCurrent ^= 1;
            current = value;
        }
    };

};

#endif
