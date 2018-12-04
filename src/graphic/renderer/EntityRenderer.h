#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Material;

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

    void bindTexture(const Material* m);

    void unbindTexture();

    void loadCamPosition(Scene* scene);

    void loadMaterial(const Material* m);

    void loadMatrices(TransMat &mat,
                      const Position* p,
                      const Rotation* r,
                      const Scale* s);

    void loadSpotLights(Scene *scene);

    void loadPointLights(Scene* scene);

    void loadDirectionalLight(Scene* scene);

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
