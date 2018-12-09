#ifndef UNIFORMFLOAT_H_
#define UNIFORMFLOAT_H_

#include "Uniform.h"

struct UniformFloat : public Uniform {


    UniformFloat(const std::string &name) : Uniform(name),
                                            first(true),
                                            current(0.0f)
                                            {};

    void load(const float &value) {
        if(first || current != value) {
            glUniform1f(location, value);
            first = false;
            current = value;
        }
    };

    bool first;
    float current;
};

#endif
