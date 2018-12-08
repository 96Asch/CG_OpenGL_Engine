#ifndef LIGHTRENDERER_H_
#define LIGHTRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Model;
struct Entity;

class Scene;
class LightRenderer : public Renderer {

public:

    LightRenderer();
    ~LightRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform,
                        const std::shared_ptr<Scene> &scene) override;

    virtual void cleanup() override;

private:

    void loadCamPosition(std::shared_ptr<Scene> scene);

    void loadSpotLights(std::shared_ptr<Scene> scene);

    void loadPointLights(std::shared_ptr<Scene> scene);

    void loadDirectionalLight(std::shared_ptr<Scene> scene);

};

#endif
