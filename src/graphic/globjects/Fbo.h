#ifndef FBO_H_
#define FBO_H_

#include "Global.h"

class Fbo {

public:

    Fbo() {};

    virtual ~Fbo() {};

    virtual bool init(const unsigned &width, const unsigned &height) = 0;

    virtual void remove() = 0;

protected:

    GLuint id;

};

#endif
