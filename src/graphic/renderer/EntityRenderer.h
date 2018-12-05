#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Material;
struct Entity;

class Scene;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, Scene *scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    virtual void preRender(TransMat &transform, Scene *scene) override;

    virtual void postRender(Scene *scene) override;

    void bindTexture(const Material* m);

    void unbindTexture();

    void loadCamPosition(Scene* scene);

    void loadMaterial(const Material* m);

    void loadMatrices(TransMat &mat,
                      const Position* p,
                      const Rotation* r,
                      const Scale* s);

    void loadExposion(Entity &e);

    void loadSpotLights(Scene* scene);

    void loadPointLights(Scene* scene);

    void loadDirectionalLight(Scene* scene);

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
