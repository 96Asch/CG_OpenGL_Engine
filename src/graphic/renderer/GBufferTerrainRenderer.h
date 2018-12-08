#ifndef GBUFFERTERRAINRENDERER_H_
#define GBUFFERTERRAINRENDERER_H_

#include "Renderer.h"

struct Terrain;
class Scene;

class GBufferTerrainRenderer : public Renderer {

public:

    GBufferTerrainRenderer();
    ~GBufferTerrainRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void setShader();

    void bindTextures(const Terrain &terrain);

    void unbindTextures();

    void loadMaterials(const Terrain &terrain);

    void loadMatrices(const Terrain &terrain, TransMat &mat);

    void buildModelMatrix(glm::mat4 &model, const glm::vec2 &position);

};

#endif
