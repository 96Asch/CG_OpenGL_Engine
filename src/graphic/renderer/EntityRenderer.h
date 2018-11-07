#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct TransformComponent;
struct Camera;

class Scene;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void render(const float &interpolation, Scene *scene) override;

private:

    glm::mat4 model, view, projection;

    virtual void preRender(const float &interpolation, Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void buildModelMatrix(const TransformComponent* transform);

    void buildViewMatrix(const float &interpolation, const Camera &camera);

    void buildProjectionMatrix();

protected:

    virtual void init() override;

    virtual void cleanup() override;

};

#endif
