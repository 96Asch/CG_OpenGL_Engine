#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/mat4x4.hpp>

#include "../shader/Shader.h"
#include "../../util/TransMat.h"

class Scene;
class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void render(const float &interpolation,
                        TransMat &transform,
                        Scene *scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

    virtual void preRender(const float &interpolation,
                           TransMat &transform,
                           Scene *scene) = 0;

    virtual void postRender(const float &interpolation, Scene *scene) = 0;

};

#endif
