#include "Vao.h"
#include <cstdarg>
#include <iostream>

Vao::Vao(const GLuint &id) : id(id), indexVbo(nullptr), indexCount(0)
{}

Vao::~Vao() {
    for(auto vbo : vbos) {
        delete vbo;
        vbo = nullptr;
    }
    if(indexVbo)
        delete indexVbo;
    vbos.clear();
    indexVbo = nullptr;
}

Vao* Vao::create() {
    GLuint id;
    glGenVertexArrays(1, &id);
    return new Vao(id);
}

int Vao::getIndexCount() {
    return indexCount;
}

void Vao::createIndexBuffer(const GLuint* indices, const GLsizei &size) {
    indexVbo = Vbo::create(GL_ELEMENT_ARRAY_BUFFER);
    indexVbo->bind();
    indexVbo->storeData(indices, size);
    indexCount = size;
}

void Vao::createAttribute(const int &attribute,
                          const GLsizei &dimension,
                          const GLfloat* data, const GLsizeiptr & dataSize) {
    Vbo* vbo = Vbo::create(GL_ARRAY_BUFFER);
    vbo->bind();
    vbo->storeData(data, dataSize);
    glVertexAttribPointer(attribute, dimension, GL_FLOAT,
                          GL_FALSE, sizeof(GLfloat) * dimension, (void*) 0);
    vbo->unbind();
    vbos.push_back(vbo);
}

void Vao::createAttribute(const int &attribute,
                          const GLsizei &dimension,
                          const GLuint* data, const GLsizeiptr & dataSize) {
    Vbo* vbo = Vbo::create(GL_ARRAY_BUFFER);
    vbo->bind();
    vbo->storeData(data, dataSize);
    glVertexAttribPointer(attribute, dimension, GL_INT,
                          GL_FALSE, sizeof(GLint) * dimension, (void*) 0);
    vbo->unbind();
    vbos.push_back(vbo);
}

void Vao::addInstancedAttribute(Vbo* vbo, const int &attribute, const GLsizei &dataSize,
                            const GLsizei &instancedLength, const GLsizei &offset) {
    vbo->bind();
    bind();
    GLsizei byteoffset = offset * sizeof(GLfloat);
    glVertexAttribPointer(attribute, dataSize, GL_FLOAT, false,
                          instancedLength * sizeof(GLfloat),
                          &byteoffset);
    glVertexAttribDivisor(attribute, 1);
    unbind();
    vbo->unbind();
    vbos.push_back(vbo);
}

void Vao::remove() {
    glDeleteVertexArrays(1, &id);
	for (auto vbo : vbos) {
		vbo->remove();
	}
	if (indexVbo)
		indexVbo->remove();
}

void Vao::bind() {
    glBindVertexArray(id);
}

void Vao::unbind() {
    glBindVertexArray(0);
}
