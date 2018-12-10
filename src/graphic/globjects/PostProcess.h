#ifndef HDR_H_
#define HDR_H_

#include "Fbo.h"

class PostProcess : public Fbo {

public:

    PostProcess(const unsigned &width, const unsigned &height);

    ~PostProcess();

    virtual void remove() override;

    void bindTextures();

    void unbindTextures();

private:


    GLuint lightBuff;
    GLuint brightBuff;
    GLuint depthBuff;

};

#endif
