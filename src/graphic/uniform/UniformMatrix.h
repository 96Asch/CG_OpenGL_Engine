#ifndef UNIFORMMATRIX_H_
#define UNIFORMMATRIX_H_
#include "Global.h"
#include "Uniform.h"

class UniformMatrix : public Uniform {

public:
    UniformMatrix(const std::string &name);

    ~UniformMatrix();

    void load(const glm::mat4 &matrix);

};

#endif
