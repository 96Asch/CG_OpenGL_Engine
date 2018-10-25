#include "UniformMatrix.h"

UniformMatrix::UniformMatrix(const std::string &name)
    : Uniform(name){}

UniformMatrix::~UniformMatrix(){}

void UniformMatrix::load(const glm::mat4 &matrix) {
    glUniformMatrix4fv(getLocation(), 1, GL_FALSE, glm::value_ptr(matrix));
}
