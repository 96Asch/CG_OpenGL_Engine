#ifndef UNIFORMFLOAT_H_
#define UNIFORMFLOAT_H_

#include "Uniform.h"

struct UniformFloat : public Uniform {

    float current;
    bool first;

    UniformFloat(const std::string &name) : Uniform(name),
                                            first(true)  {};

    void load(const float &value) {
        if(first || current != value) {
            glUniform1f(location, value);
            first = false;
            current = value;
        }
    };

};

#endif
