#ifndef SKYBOXRENDERER_H_
#define SKYBOXRENDERER_H_

#include "Renderer.h"

struct Skybox;

class SkyboxRenderer : public Renderer {

public:

    SkyboxRenderer();

    virtual ~SkyboxRenderer() override;

    virtual void init() override;

    virtual void render(const float &interpolation,
                        TransMat &mat,
                        Scene *scene) override;

    virtual void cleanup() override;

protected:

    virtual void preRender(const float &interpolation,
                           TransMat &mat,
                           Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void buildProjectionViewMatrix(TransMat &mat, Skybox &box);
};

#endif
