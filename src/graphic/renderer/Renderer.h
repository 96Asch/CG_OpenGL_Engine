#ifndef RENDERER_H_
#define RENDERER_H_

#include "../shader/Shader.h"

class Scene;
class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void render(const float &interpolation, Scene *scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

    virtual void preRender(const float &interpolation, Scene *scene) = 0;

    virtual void postRender(const float &interpolation, Scene *scene) = 0;

};

#endif
