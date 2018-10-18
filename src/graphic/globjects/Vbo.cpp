#include "Vbo.h"

Vbo::Vbo(const GLenum &target, const GLuint &id)
        : target(target), id(id) {}

Vbo::~Vbo() {}

Vbo* Vbo::create(const GLenum &target) {
    GLuint id;
    glGenBuffers(1, &id);
    return new Vbo(target, id);
}

Vbo* Vbo::createEmpty(const int &numFloats) {
    Vbo* vbo = create(GL_ARRAY_BUFFER);
    vbo->bind();
    vbo->storeData(numFloats);
    vbo->unbind();
    return vbo;
}

void Vbo::bind() {
    glBindBuffer(target, id);
}

void Vbo::unbind() {
    glBindBuffer(target, 0);
}

void Vbo::storeData(const GLsizei &size) {
    glBufferData(target, size * BYTES_PER_FLOAT, 0, GL_STREAM_DRAW);
}

void Vbo::update(float* data, const GLsizei &size) {
    bind();
    storeData(size);
    glBufferSubData(target, 0, size, data);
    unbind();
}

void Vbo::remove() {
    glDeleteBuffers(1, &id);
}
