#ifndef RENDERER_H_
#define RENDERER_H_

#include <glm/mat4x4.hpp>
#include <memory>

#include "../shader/Shader.h"
#include "../../util/TransMat.h"

class Scene;
class Renderer {

public:

    Renderer() = default;

    virtual ~Renderer() = default;

    virtual void init() = 0;

    virtual void render(TransMat &transform,
                        std::shared_ptr<Scene> scene) = 0;

    virtual void cleanup() = 0;

protected:

    Shader shader;

};

#endif
