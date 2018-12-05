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

    virtual void render(TransMat &transform,
                        Scene *scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

    virtual void preRender(TransMat &transform, Scene *scene) = 0;

    virtual void postRender(Scene *scene) = 0;

};

#endif
