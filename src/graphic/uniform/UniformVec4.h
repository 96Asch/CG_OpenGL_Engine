#ifndef UNIFORMVEC4_H_
#define UNIFORMVEC4_H_

#include <glm/vec4.hpp>

#include "Uniform.h"

struct UniformVec4 : public Uniform {

    UniformVec4(const std::string &name) : Uniform(name),
                                           first(true),
                                           current(glm::vec4(0.0f))
                                           {};

    void load(const glm::vec4 &vector) {
        if(first || current != vector) {
            current = vector;
            first = false;
            glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
        }
    };

    void load(const float &v1, const float &v2, const float &v3, const float &v4) {
        load(glm::vec4(v1, v2, v3, v4));
    };

    bool first;
    glm::vec4 current;

};

#endif
