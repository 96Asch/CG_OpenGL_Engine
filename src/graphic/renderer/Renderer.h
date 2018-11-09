#ifndef RENDERER_H_
#define RENDERER_H_

#include "../shader/Shader.h"
#include <glm/mat4x4.hpp>

class Scene;
class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init(const glm::mat4 &projection) = 0;

    virtual void render(const float &interpolation,
                        const glm::mat4 &view,
                        Scene *scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

    virtual void preRender(const float &interpolation,
                           const glm::mat4 &view,
                           Scene *scene) = 0;

    virtual void postRender(const float &interpolation, Scene *scene) = 0;

};

#endif
