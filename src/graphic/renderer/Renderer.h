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

    template <typename T>
    T lerp(const T &start, const T &end, const float &alpha);

};

template <typename T>
T Renderer::lerp(const T &start, const T &end, const float &alpha) {
    return (start * (1 - alpha) + end * alpha); 
}

#endif
