#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Transform;

class Scene;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void init() override;

    virtual void render(const float &interpolation,
                        TransMat &transform,
                        Scene *scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    virtual void preRender(const float &interpolation,
                           TransMat &transform,
                           Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void loadMatrices(TransMat &mat);

    void loadPointLights(const glm::mat4 &view, Scene* scene);

    void loadDirectionalLight(const glm::mat4 &view, Scene* scene);

    void buildModelMatrix(glm::mat4 &model, const Transform* t, const float &interpolation);

};

#endif
