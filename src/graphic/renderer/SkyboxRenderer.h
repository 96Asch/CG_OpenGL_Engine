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
                        const glm::mat4 &view,
                        const glm::mat4 &projection,
                        Scene *scene) override;

    virtual void cleanup() override;

protected:

    void setupShader();

    virtual void preRender(const float &interpolation,
                           const glm::mat4 &view,
                           const glm::mat4 &projection,
                           Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void buildProjectionViewMatrix(glm::mat4 &pv,
                                   Skybox &box,
                                   const glm::mat4 &view,
                                   const glm::mat4 &projection);
};

#endif
