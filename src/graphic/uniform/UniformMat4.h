#ifndef UNIFORMMAT_H_
#define UNIFORMMAT_H_

#include <glm/mat4x4.hpp>

#include "Uniform.h"

struct UniformMat4 : public Uniform {

    UniformMat4(const std::string &name) : Uniform(name) {};

    void load(const glm::mat4 &matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

};

#endif
