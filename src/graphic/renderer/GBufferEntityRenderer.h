#ifndef GBUFFERENTITYRENDERER_H_
#define GBUFFERENTITYRENDERER_H_

#include "Renderer.h"

struct Position;
struct Rotation;
struct Scale;
struct Model;
struct Entity;

class Scene;
class GBufferEntityRenderer : public Renderer {

public:

    GBufferEntityRenderer();
    ~GBufferEntityRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    void bindTexture(const Model* m);

    void unbindTexture();

    void loadMatrices(TransMat &mat,
                      const Position* p,
                      const Rotation* r,
                      const Scale* s);

    void loadExposion(Entity &e);

    void buildModelMatrix(glm::mat4 &model,
                          const Position* p,
                          const Rotation* r,
                          const Scale* s);

};

#endif
