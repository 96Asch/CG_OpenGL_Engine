#ifndef UNIFORMVEC3_H_
#define UNIFORMVEC3_H_

#include <glm/vec3.hpp>

#include "Uniform.h"

struct UniformVec3 : public Uniform {


    UniformVec3(const std::string &name) : Uniform(name),
                                           first(true),
                                           current(glm::vec3(0.0f))
                                           {};

    void load(const glm::vec3 &vector) {
        if(first || current != vector) {
            current = vector;
            first = false;
            glUniform3f(location, vector.x, vector.y, vector.z);
        }
    };

    void load(const float &v1, const float &v2, const float &v3) {
        load(glm::vec3(v1,v2,v3));
    };

    bool first;
    glm::vec3 current;

};

#endif
