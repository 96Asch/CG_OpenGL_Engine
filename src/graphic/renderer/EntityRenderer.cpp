#include <glm/mat4x4.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    shader.init("shader/entity", "position", "texCoord", "vertexNormal", "tangent");
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformVec3("ambientLight"));
    shader.addUniform(new UniformVec3("camPosition"));
    shader.addUniform(new UniformMaterial("material"));
    shader.addUniform(new UniformSampler("texture"));
    shader.addUniform(new UniformSampler("shadowMap"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformSLights("spotLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.addUniform(new UniformFog("fog"));
    shader.storeUniformLocations();
}

void EntityRenderer::preRender(TransMat &, Scene* ) {


}

void EntityRenderer::render(TransMat &matrices, Scene *scene) {
    // GLUtil::cullBackFaces(true);
    GLUtil::enableDepthTesting(true);
    shader.start();
    loadSpotLights(scene);
    loadPointLights(scene);
    loadDirectionalLight(scene);
    loadCamPosition(scene);
    shader.getUniform<UniformFog>("fog")->load(scene->getFog());
    shader.getUniform<UniformSampler>("shadowMap")->loadTexUnit(0);
    shader.getUniform<UniformSampler>("texture")->loadTexUnit(1);
    shader.getUniform<UniformVec3>("ambientLight")->load(scene->getAmbient());
    for(auto e : scene->getEntities().withComponents<Model, Material, Position, Rotation, Scale>()) {
        Model* mod = e.getComponent<Model>();
        const Material* mat = e.getComponent<Material>();
        const Position* pos = e.getComponent<Position>();
        const Rotation* rot = e.getComponent<Rotation>();
        const Scale* sca = e.getComponent<Scale>();

        loadMaterial(mat);
        loadMatrices(matrices, pos, rot, sca);

        mod->getVao()->bind(0,1,2);
        bindTexture(mat);
        glDrawElements(GL_TRIANGLES, mod->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        unbindTexture();
        mod->getVao()->unbind(0,1,2);
    }
    shader.stop();
    // GLUtil::cullBackFaces(false);
    GLUtil::enableDepthTesting(false);
};

void EntityRenderer::postRender(Scene*) {

}

void EntityRenderer::cleanup() {
    shader.cleanup();
}

void EntityRenderer::loadCamPosition(Scene* scene) {
    glm::vec3 position(glm::vec3(0.0f));
    for(auto e : scene->getEntities().withComponents<Camera, Position>()) {
        position = e.getComponent<Position>()->interpolated;
    }
    shader.getUniform<UniformVec3>("camPosition")->load(position);
}


void EntityRenderer::bindTexture(const Material* m) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m->id);
}

void EntityRenderer::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void EntityRenderer::loadMaterial(const Material* m) {
    shader.getUniform<UniformMaterial>("material")->load(*m);
}

void EntityRenderer::loadMatrices(TransMat &mat,
                                  const Position* p,
                                  const Rotation* r,
                                  const Scale* s)
{
    buildModelMatrix(mat.model, p, r ,s);
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mv = mat.view * mat.model;
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void EntityRenderer::loadPointLights(Scene *scene) {
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

void EntityRenderer::loadSpotLights(Scene *scene) {
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

void EntityRenderer::loadDirectionalLight(Scene *scene) {
    shader.getUniform<UniformDLight>("directionalLight")->load(scene->getDirectional());
}
void EntityRenderer::buildModelMatrix(glm::mat4 &model,
                                      const Position* p,
                                      const Rotation* r,
                                      const Scale* s)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, p->interpolated);
    model = glm::rotate(model, glm::radians(r->interpolated.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(r->interpolated.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(r->interpolated.z), glm::vec3(0,0,1));
    model = glm::scale(model, s->interpolated);
}
