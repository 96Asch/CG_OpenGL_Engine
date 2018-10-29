#ifndef RENDERER_H_
#define RENDERER_H_

#include "../shader/Shader.h"

class Scene;
class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void render(Scene *scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

    virtual void preRender(Scene *scene) = 0;

    virtual void postRender(Scene *scene) = 0;

};

#endif
