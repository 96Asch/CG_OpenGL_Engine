#ifndef FBO_H_
#define FBO_H_

#include "Global.h"

class Fbo {

public:

    Fbo() {};

    virtual ~Fbo() {};

    virtual void bind() = 0;

    void unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    virtual void remove() = 0;

protected:

    GLuint id;

};

#endif
