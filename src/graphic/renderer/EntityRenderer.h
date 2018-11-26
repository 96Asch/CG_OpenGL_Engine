#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Transform;
struct Camera;

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

    glm::mat4 model;

    virtual void preRender(const float &interpolation,
                           const glm::mat4 &view,
                           Scene *scene) override;

    virtual void postRender(const float &interpolation, Scene *scene) override;

    void buildModelMatrix(const Transform* transform);

};

#endif
