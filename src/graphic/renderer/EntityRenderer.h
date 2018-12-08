#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Model;
struct Entity;

class Scene;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    void bindTexture(const Model* m);

    void unbindTexture();

    void loadCamPosition(std::shared_ptr<Scene> scene);

    void loadMatrices(TransMat &mat,
                      const Position* p,
                      const Rotation* r,
                      const Scale* s);

    void loadExposion(Entity &e);

    void loadSpotLights(std::shared_ptr<Scene> scene);

    void loadPointLights(std::shared_ptr<Scene> scene);

    void loadDirectionalLight(std::shared_ptr<Scene> scene);

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
