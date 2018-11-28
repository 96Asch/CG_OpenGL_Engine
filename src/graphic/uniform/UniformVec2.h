#ifndef UNIFORMVEC2_H_
#define UNIFORMVEC2_H_

#include <glm/vec2.hpp>

#include "Uniform.h"

struct UniformVec2 : public Uniform {


    UniformVec2(const std::string &name) : Uniform(name),
                                           first(true){};

    void load(const glm::vec2 &vector) {
        if(first || current != vector) {
            current = vector;
            first = false;
            glUniform2f(location, vector.x, vector.y);
        }
    };

    void load(const float &v1, const float &v2) {
        load(glm::vec2(v1, v2));
    };

    glm::vec2 current;
    bool first;

};

#endif
