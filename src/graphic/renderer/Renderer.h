#ifndef RENDERER_H_
#define RENDERER_H_

#include "../shader/Shader.h"

class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void render() = 0;

    virtual void cleanup() = 0;

protected:
    Shader shader;

    virtual void preRender() = 0;

    virtual void postRender() = 0;

};

#endif RENDERER_H_
