#ifndef TRANSMAT_H_
#define TRANSMAT_H_

#include <glm/mat4x4.hpp>

struct TransMat {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 mv;
    glm::mat4 pv;
    glm::mat4 mvp;
};

#endif
