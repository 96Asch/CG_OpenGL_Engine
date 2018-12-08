#ifndef TERRAINRENDERER_H_
#define TERRAINRENDERER_H_

#include "Renderer.h"

struct Terrain;

class TerrainRenderer : public Renderer {

public:

    TerrainRenderer();

    virtual ~TerrainRenderer() override;

    virtual void init() override;

    virtual void render(TransMat &mat, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

protected:

    void bindTextures(const Terrain &terrain);

    void unbindTextures(const Terrain &terrain);

    void loadCamPosition(std::shared_ptr<Scene> scene);

    void loadMaterials(const Terrain &terrain);

    void loadMatrices(const Terrain &terrain, TransMat &mat);

    void loadSpotLights(std::shared_ptr<Scene> scene);

    void loadPointLights(std::shared_ptr<Scene> scene);

    void loadDirectionalLight(std::shared_ptr<Scene> scene);

    void buildModelMatrix(glm::mat4 &model, const glm::vec2 &position);

};

#endif
