#ifndef UNIFORMINT_H_
#define UNIFORMINT_H_

#include "Uniform.h"

struct UniformInt : public Uniform {


    UniformInt(const std::string &name) : Uniform(name),
                                            first(true)  {};

    void load(const int &value) {
        if(first || current != value) {
            glUniform1i(location, value);
            first = false;
            current = value;
        }
    };

    int current;
    bool first;
};

#endif
