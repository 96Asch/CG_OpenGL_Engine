#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Transform;

class Scene;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void init(const glm::mat4 &projection) override;

    virtual void render(const float &interpolation,
                        const glm::mat4 &view,
                        Scene *scene) override;

    virtual void cleanup() override;

private:

    virtual void preRender(const float &interpolation,
                           const glm::mat4 &view,
                           Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void loadPointLights(const glm::mat4 &view, Scene* scene);

    void loadDirectionalLight(const glm::mat4 &view, Scene* scene);

    glm::mat4 buildModelMatrix(const Transform* t, const float &interpolation);

};

#endif
