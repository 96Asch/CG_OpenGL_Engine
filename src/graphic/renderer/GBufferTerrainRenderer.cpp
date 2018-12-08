#include "GBufferTerrainRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"
#include "../../environment/Terrain.h"

GBufferTerrainRenderer::GBufferTerrainRenderer() {}

GBufferTerrainRenderer::~GBufferTerrainRenderer() {}

void GBufferTerrainRenderer::init() {
    shader.init("shader/terrain-gbuffer.vs", "shader/terrain-gbuffer.fs",
                {"position", "uv", "normal"});
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformInt("numMaterials"));
    shader.addUniform(new UniformInts("texDiffuse", 5));
    shader.addUniform(new UniformFloats("specular", 4));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformInts>("texDiffuse")->load({0,1,2,3,4});
    shader.stop();
}

void GBufferTerrainRenderer::render(TransMat &mat,
                                    const std::shared_ptr<Scene> &scene)
{
    Terrain &terrain = scene->getTerrain();
    GLUtil::cullBackFaces(true);
    shader.start();
    loadMatrices(terrain, mat);
    loadMaterials(terrain);
    terrain.getVao()->bind();
    bindTextures(terrain);
    glDrawElements(GL_TRIANGLES, terrain.getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
    unbindTextures();
    terrain.getVao()->unbind();
    shader.stop();
    GLUtil::cullBackFaces(false);
}

void GBufferTerrainRenderer::cleanup() {
    shader.cleanup();
}

void GBufferTerrainRenderer::bindTextures(const Terrain &terrain) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrain.blendMap);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, terrain.getTexture(i));
    }
}

void GBufferTerrainRenderer::unbindTextures() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GBufferTerrainRenderer::loadMaterials(const Terrain &terrain) {
    shader.getUniform<UniformInt>("numMaterials")->load(terrain.numMaterials);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        shader.getUniform<UniformFloats>("specular")
                ->load(terrain.textures[i].reflectance, i);
    }
}

void GBufferTerrainRenderer::loadMatrices(const Terrain &terrain, TransMat &mat) {
    buildModelMatrix(mat.model, terrain.position);
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mv = mat.view * mat.model;
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void GBufferTerrainRenderer::buildModelMatrix(glm::mat4 &model, const glm::vec2 &position) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, 0, position.y));
    model = glm::scale(model, glm::vec3(1.0f));
}
