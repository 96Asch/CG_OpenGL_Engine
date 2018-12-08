#ifndef ENTITYLIGHTRENDERER_H_
#define ENTITYLIGHTRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Model;
struct Entity;

class Scene;
class EntityLightRenderer : public Renderer {

public:

    EntityLightRenderer();
    ~EntityLightRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void loadCamPosition(std::shared_ptr<Scene> scene);

    void loadSpotLights(std::shared_ptr<Scene> scene);

    void loadPointLights(std::shared_ptr<Scene> scene);

    void loadDirectionalLight(std::shared_ptr<Scene> scene);

};

#endif
