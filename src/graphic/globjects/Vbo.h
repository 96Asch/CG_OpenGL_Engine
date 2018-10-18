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

    template <typename T>
    void storeData(T* data, const GLsizei &size) {
        glBufferData(target, size, data, GL_STATIC_DRAW);
    }

    void storeData(const GLsizei &size);

    void update(float* data, const GLsizei &size);

    void remove();

private:
    GLenum target;
    GLuint id;

    Vbo(const GLenum &target, const GLuint &id);

};

#endif
