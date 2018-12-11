#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <string>
#include "Global.h"

struct Uniform {

    std::string name;

    GLint location;

    Uniform(const std::string &name) : name(name) {};

    virtual ~Uniform(){};

    virtual void storeUniformLocation(const GLuint &id) {
        location = glGetUniformLocation(id, name.c_str());
        if(location == -1)
            fprintf(stderr, "Could not find uniform: %s\n", name.c_str());
    }
};

#endif
