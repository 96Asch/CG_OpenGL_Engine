#ifndef VBO_H_
#define VBO_H_

#include <memory>

#include "Global.h"

class Vbo {

public:
    Vbo(const GLenum &target, const GLuint &id);

    ~Vbo();

    static std::shared_ptr<Vbo> create(const GLenum &target);

    static std::shared_ptr<Vbo> createEmpty(const int &numFloats);

    void bind();

    void unbind();

    void storeData(const GLfloat* data, const GLsizeiptr &size);

    void storeData(const GLuint* data, const GLsizeiptr &size);

    void storeEmpty(const GLsizei &size);

    void update(float* data, const GLsizei &size);

    void remove();

private:
    GLenum target;
    GLuint id;

};

#endif
