#ifndef UNIFORMMATRIX_H_
#define UNIFORMMATRIX_H_

#include "Global.h"
#include "Uniform.h"

struct UniformMatrix : public Uniform {

    UniformMatrix(const std::string &name) : Uniform(name) {};

    void load(const glm::mat4 &matrix) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

};

#endif
