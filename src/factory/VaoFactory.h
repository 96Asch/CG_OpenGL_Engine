#ifndef VAOFACTORY_H_
#define VAOFACTORY_H_

#include <vector>

#include "../graphic/globjects/Vao.h"

class VaoFactory {

public:

    VaoFactory();
    ~VaoFactory();

    Vao* createVao(GLfloat* position, GLuint posSize,
                   GLuint* indices, GLuint indiceSize);

    Vao* createVao(GLfloat* position, GLuint posSize,
                   GLuint* indices, GLuint indiceSize,
                   GLfloat* texture, GLuint texSize);

    Vao* createVao(GLfloat* position, GLuint posSize,
                   GLfloat* texture, GLuint texSize,
                   GLfloat* normals, GLuint normalSize,
                   GLuint* indices, GLuint indiceSize);
    void removeVao();

private:

    std::vector<Vao*> vaos;


};

#endif
