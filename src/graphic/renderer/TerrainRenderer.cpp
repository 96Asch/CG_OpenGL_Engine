#include "TerrainRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"
#include "../../environment/Terrain.h"

TerrainRenderer::TerrainRenderer() {}

TerrainRenderer::~TerrainRenderer() {}

void TerrainRenderer::init() {
    shader.init("shader/terrain.vs", "shader/terrain.fs", {"position", "uv", "normal"});
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformInt("numMaterials"));
    shader.addUniform(new UniformVec3("ambientLight"));
    shader.addUniform(new UniformVec3("camPosition"));
    shader.addUniform(new UniformSpeculars("specular", 4));
    shader.addUniform(new UniformSamplers("textures"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformSLights("spotLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformSamplers>("textures")->loadTexUnits(1);
    shader.stop();
}

void TerrainRenderer::render(TransMat &mat, Scene *scene) {
    Terrain &terrain = scene->getTerrain();
    GLUtil::cullBackFaces(true);
    shader.start();
    shader.getUniform<UniformVec3>("ambientLight")->load(scene->getAmbient());

    loadDirectionalLight(scene);
    loadPointLights(scene);
    loadSpotLights(scene);
    loadCamPosition(scene);

    loadMatrices(terrain, mat);
    terrain.getVao()->bind(0,1,2);
    bindTextures(terrain);
    loadMaterials(terrain);
    glDrawElements(GL_TRIANGLES, terrain.getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
    unbindTextures(terrain);
    terrain.getVao()->unbind(0,1,2);
    shader.stop();
    GLUtil::cullBackFaces(false);
}

void TerrainRenderer::cleanup() {
    shader.cleanup();
}


void TerrainRenderer::preRender(TransMat &, Scene *) {


}

void TerrainRenderer::postRender(Scene *) {

}

void TerrainRenderer::loadCamPosition(Scene* scene) {
    glm::vec3 position(glm::vec3(0.0f));
    for(auto e : scene->getEntities().withComponents<Camera, Position>()) {
        position = e.getComponent<Position>()->interpolated;
    }
    shader.getUniform<UniformVec3>("camPosition")->load(position);
}


void TerrainRenderer::bindTextures(const Terrain &terrain) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, terrain.blendMap);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        glActiveTexture(GL_TEXTURE2 + i);
        glBindTexture(GL_TEXTURE_2D, terrain.getTexture(i));
    }
}

void TerrainRenderer::unbindTextures(const Terrain &terrain) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}

void TerrainRenderer::loadMaterials(const Terrain &terrain) {
    shader.getUniform<UniformInt>("numMaterials")->load(terrain.numMaterials);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        shader.getUniform<UniformSpeculars>("specular")
                ->load(terrain.textures[i].specularPower,
                        terrain.textures[i].reflectance, i);
    }
}

void TerrainRenderer::loadMatrices(const Terrain &terrain, TransMat &mat) {
    buildModelMatrix(mat.model, terrain.position);
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mv = mat.view * mat.model;
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void TerrainRenderer::loadPointLights(Scene *scene) {
    unsigned counter = 0;
    for(auto light : scene->getEntities().withComponents<PointLight, Position>()) {
        PointLight* pl = light.getComponent<PointLight>();
        Position* pos = light.getComponent<Position>();
        shader.getUniform<UniformPLights>("pointLight")->load(*pl, pos->interpolated, counter);
        ++counter;
    }
    while(counter < Global::MAX_POINT_LIGHTS) {
        shader.getUniform<UniformPLights>("pointLight")->loadEmpty(counter);
        ++counter;
    }
}

void TerrainRenderer::loadSpotLights(Scene *scene) {
    unsigned counter = 0;
    for(auto light : scene->getEntities().withComponents<SpotLight, Position, LookAt>()) {
        SpotLight* pl = light.getComponent<SpotLight>();
        Position* pos = light.getComponent<Position>();
        LookAt* look = light.getComponent<LookAt>();
        shader.getUniform<UniformSLights>("spotLight")->load(*pl,
                                                             pos->interpolated,
                                                             look->interpolated,
                                                             counter);
        ++counter;
    }
    while(counter < Global::MAX_SPOT_LIGHTS) {
        shader.getUniform<UniformSLights>("spotLight")->loadEmpty(counter);
        ++counter;
    }
}

void TerrainRenderer::loadDirectionalLight(Scene *scene) {
    shader.getUniform<UniformDLight>("directionalLight")->load(scene->getDirectional());
}

void TerrainRenderer::buildModelMatrix(glm::mat4 &model, const glm::vec2 &position) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, 0, position.y));
    model = glm::scale(model, glm::vec3(1.0f));
}
