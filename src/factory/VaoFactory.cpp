#include "VaoFactory.h"


#define SIZE_3D 3
#define SIZE_2D 2

VaoFactory::VaoFactory() = default;

VaoFactory::~VaoFactory() {
    for(auto vao : vaos) {
        vao->remove();
        delete vao;
    }
}

Vao* VaoFactory::createVao(GLfloat* position, GLuint posSize,
                           GLuint* indices, GLuint indiceSize) {
    Vao* vao = Vao::create();
    vao->bind();
    vao->createIndexBuffer(indices, indiceSize);
    vao->createAttribute(0, SIZE_3D, position, posSize);
    vao->unbind();
    vaos.push_back(vao);
    return vao;
}

Vao* VaoFactory::createVao(GLfloat* position, GLuint posSize,
                           GLuint* indices, GLuint indiceSize,
                           GLfloat* texture, GLuint texSize) {
    Vao* vao = Vao::create();
    vao->bind();
    vao->createIndexBuffer(indices, posSize);
    vao->createAttribute(0, SIZE_3D, position, posSize);
    vao->createAttribute(1, SIZE_2D, texture, texSize);
    vao->unbind();
    vaos.push_back(vao);
    return vao;                           
}

Vao* VaoFactory::createVao(GLfloat* position, GLuint posSize,
                           GLfloat* texture, GLuint texSize,
                           GLfloat* normals, GLuint normalSize,
                           GLuint* indices, GLuint indiceSize) {
    Vao* vao = Vao::create();
    vao->bind();
    vao->createIndexBuffer(indices, indiceSize);
    vao->createAttribute(0, SIZE_3D, position, posSize);
    vao->createAttribute(1, SIZE_2D, texture, texSize);
    vao->createAttribute(2, SIZE_3D, normals, normalSize);
    vao->unbind();
    vaos.push_back(vao);
    return vao;
}
