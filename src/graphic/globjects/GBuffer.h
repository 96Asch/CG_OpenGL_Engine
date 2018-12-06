#ifndef GBUFFER_H_
#define GBUFFER_H_

#include "Fbo.h"

class GBuffer : public Fbo {

public:

    GBuffer(const unsigned &width, const unsigned &height);

    virtual ~GBuffer();

    virtual void bind() override;

    virtual void remove() override;

    void bindTextures();

private:

    GLuint positionBuff;
    GLuint normalBuff;
    GLuint colorSpecBuff;
    GLuint depthBuff;

};

#endif
