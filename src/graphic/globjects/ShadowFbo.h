#ifndef SHADOWFBO_H_
#define SHADOWFBO_H_

#include "Global.h"
#include "Fbo.h"

class ShadowFbo : public Fbo{
public:
    ShadowFbo();

    virtual ~ShadowFbo();

    virtual bool init(const unsigned &width, const unsigned &height) override;

    virtual void remove();

    void bindForWriting();

    void bindForReading(GLenum texUnit);

    void unbind();

    void unbindTexture();

private:

    GLenum texUnit;
    GLuint shadowMap;
};


#endif
