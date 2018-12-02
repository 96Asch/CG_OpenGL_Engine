#include "TerrainRenderer.h"
#include "Uniforms.h"
#include "../../engine/Scene.h"
#include "../../environment/Terrain.h"

TerrainRenderer::TerrainRenderer() {}

TerrainRenderer::~TerrainRenderer() {}

void TerrainRenderer::init() {
    shader.init("shader/terrain", "position", "uv", "normal");
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mv"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformInt("numMaterials"));
    shader.addUniform(new UniformTerrainMaterials("materials"));
    shader.addUniform(new UniformSamplers("textures"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.addUniform(new UniformFog("fog"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformSamplers>("textures")->loadTexUnits();
    shader.stop();
}

void TerrainRenderer::render(const float &interpolation,
                             TransMat &mat,
                             Scene *scene)
{
    Terrain &terrain = scene->getTerrain();
    if(terrain.active) {
        preRender(interpolation, mat, scene);

        buildModelMatrix(mat.model, terrain.position);
        loadMatrices(mat);
        shader.getUniform<UniformFog>("fog")->load(scene->getFog());
        loadMaterials(terrain);
        terrain.getVao()->bind(0,1,2);
        loadTextures(terrain);
        glDrawElements(GL_TRIANGLES, terrain.getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        terrain.getVao()->unbind(0,1,2);

        postRender(interpolation, scene);
    }
}

void TerrainRenderer::cleanup() {
    shader.cleanup();
}


void TerrainRenderer::preRender(const float &,
                                TransMat &mat,
                                Scene *scene)
{
    shader.start();
    loadDirectionalLight(mat.view, scene);
    loadPointLights(mat.view, scene);
}

void TerrainRenderer::postRender(const float &, Scene *) {
    shader.stop();
}

void TerrainRenderer::loadTextures(const Terrain &terrain) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, terrain.blendMap);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        glActiveTexture(GL_TEXTURE1 + i);
        glBindTexture(GL_TEXTURE_2D, terrain.materials[i].id);
    }
}

void TerrainRenderer::loadMaterials(const Terrain &terrain) {
    shader.getUniform<UniformInt>("numMaterials")->load(terrain.numMaterials);
    for(unsigned i = 0; i < terrain.numMaterials; ++i) {
        shader.getUniform<UniformTerrainMaterials>("materials")->load(terrain.materials[i], i);
    }
}

void TerrainRenderer::loadMatrices(TransMat &mat) {
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mv = mat.view * mat.model;
    shader.getUniform<UniformMat4>("mv")->load(mat.mv);
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void TerrainRenderer::loadPointLights(const glm::mat4 &view, Scene *scene) {
    std::vector<PointLight> eyeSpacePLights;
    for(auto light : scene->getEntities().withComponents<PointLight>()) {
        PointLight copy = *(light.getComponent<PointLight>());
        glm::vec4 aux = glm::vec4(copy.position, 1);
        aux = view * aux;
        copy.position = glm::vec3(aux);
        eyeSpacePLights.push_back(copy);
    }
    shader.getUniform<UniformPLights>("pointLight")->load(eyeSpacePLights);
}

void TerrainRenderer::loadDirectionalLight(const glm::mat4 &view, Scene *scene) {
    DirectionalLight light = scene->getDirectional();
    glm::vec4 aux = glm::vec4(light.direction, 0);
    aux = view * aux;
    light.direction = glm::vec3(aux.x, aux.y, aux.z);
    shader.getUniform<UniformDLight>("directionalLight")->load(light);
}

void TerrainRenderer::buildModelMatrix(glm::mat4 &model, const glm::vec2 &position) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position.x, 0, position.y));
    model = glm::scale(model, glm::vec3(1.0f));
}
