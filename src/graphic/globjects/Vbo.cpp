#include "Vbo.h"

Vbo::Vbo(const GLenum &target, const GLuint &id)
        : target(target), id(id) {}

Vbo::~Vbo() {}

std::shared_ptr<Vbo> Vbo::create(const GLenum &target) {
    GLuint id;
    glGenBuffers(1, &id);
    return std::make_shared<Vbo>(target, id);
}

std::shared_ptr<Vbo> Vbo::createEmpty(const int &numFloats) {
    auto vbo = create(GL_ARRAY_BUFFER);
    vbo->bind();
    vbo->storeEmpty(numFloats);
    vbo->unbind();
    return vbo;
}

void Vbo::bind() {
    glBindBuffer(target, id);
}

void Vbo::unbind() {
    glBindBuffer(target, 0);
}

void Vbo::storeData(const GLfloat* data, const GLsizeiptr &size) {
    glBufferData(target, sizeof(GLfloat) * size, data, GL_STATIC_DRAW);
}

void Vbo::storeData(const GLuint* data, const GLsizeiptr &size) {
    glBufferData(target, sizeof(GLint) * size, data, GL_STATIC_DRAW);
}

void Vbo::storeEmpty(const GLsizei &size) {
    glBufferData(target, size * sizeof(GLfloat), 0, GL_STREAM_DRAW);
}

void Vbo::update(float* data, const GLsizei &size) {
    bind();
    storeEmpty(size);
    glBufferSubData(target, 0, size, data);
    unbind();
}

void Vbo::remove() {
    glDeleteBuffers(1, &id);
}
