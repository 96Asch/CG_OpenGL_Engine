#ifndef GBUFFERRENDERER_H_
#define GBUFFERRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Material;
struct Entity;

class Scene;
class GBufferRenderer : public Renderer {

public:

    GBufferRenderer();
    ~GBufferRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, Scene *scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    virtual void preRender(TransMat &transform, Scene *scene) override;

    virtual void postRender(Scene *scene) override;

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
