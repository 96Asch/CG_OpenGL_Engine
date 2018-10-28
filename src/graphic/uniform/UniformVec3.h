#ifndef UNIFORMVEC3_H_
#define UNIFORMVEC3_H_

#include <glm/vec3.hpp>

#include "Uniform.h"

struct UniformVec3 : public Uniform {

    glm::vec3 current;
    bool first;

    UniformVec3(const std::string &name) : Uniform(name),
                                           first(true){};

    void load(const glm::vec3 vector) {
        if(first || current != vector) {
            current = vector;
            first = false;
            glUniform3f(location, vector.x, vector.y, vector.z);
        }
    };


};

#endif
