#ifndef SKYBOXRENDERER_H_
#define SKYBOXRENDERER_H_

#include "Renderer.h"

struct Skybox;

class SkyboxRenderer : public Renderer {

public:

    SkyboxRenderer();

    virtual ~SkyboxRenderer() override;

    virtual void init() override;

    virtual void render(TransMat &mat, const std::shared_ptr<Scene> &scene) override;

    virtual void cleanup() override;

protected:

    void buildProjectionViewMatrix(TransMat &mat, Skybox &box);
};

#endif
