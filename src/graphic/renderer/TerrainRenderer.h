#ifndef TERRAINRENDERER_H_
#define TERRAINRENDERER_H_

#include "Renderer.h"

struct Terrain;

class TerrainRenderer : public Renderer {

public:

    TerrainRenderer();

    virtual ~TerrainRenderer() override;

    virtual void init() override;

    virtual void render(TransMat &mat, Scene *scene) override;

    virtual void cleanup() override;

protected:

    virtual void preRender(TransMat &mat, Scene *scene) override;

    virtual void postRender(Scene *scene) override;

    void bindTextures(const Terrain &terrain);

    void unbindTextures(const Terrain &terrain);

    void loadCamPosition(Scene* scene);

    void loadMaterials(const Terrain &terrain);

    void loadMatrices(const Terrain &terrain, TransMat &mat);

    void loadSpotLights(Scene *scene);

    void loadPointLights(Scene* scene);

    void loadDirectionalLight(Scene* scene);

    void buildModelMatrix(glm::mat4 &model, const glm::vec2 &position);

};

#endif
