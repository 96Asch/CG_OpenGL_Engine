#ifndef VBO_H_
#define VBO_H_

#include "Global.h"


class Vbo {

public:

    ~Vbo();

    static Vbo* create(const GLenum &target);

    static Vbo* createEmpty(const int &numFloats);

    void bind();
    void unbind();

    void storeData(GLfloat* data, const GLsizeiptr &size);
    void storeData(GLuint* data, const GLsizeiptr &size);

    void storeEmpty(const GLsizei &size);

    void update(float* data, const GLsizei &size);

    void remove();

private:
    GLenum target;
    GLuint id;

    Vbo(const GLenum &target, const GLuint &id);

};

#endif
