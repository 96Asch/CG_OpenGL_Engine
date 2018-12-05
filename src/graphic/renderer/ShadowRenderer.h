#ifndef SHADOWRENDERER_H_
#define SHADOWRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Material;

class ShadowRenderer : public Renderer {

public:

    ShadowRenderer();

    virtual ~ShadowRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, Scene *scene) override;

    virtual void cleanup() override;

protected:

    virtual void preRender(TransMat &transform, Scene *scene) override;

    virtual void postRender(Scene *scene) override;

    void loadMVP(TransMat &mat,
                 const Position* p,
                 const Rotation* r,
                 const Scale* s);

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
