#include <glm/mat4x4.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    shader.init("shader/entity.vs", "shader/entity.fs", "shader/entity.gs",
                {"position", "uv", "normal"});
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformVec3("ambientLight"));
    shader.addUniform(new UniformFloat("explodeDistance"));
    shader.addUniform(new UniformFloat("explodeActive"));
    shader.addUniform(new UniformVec3("camPosition"));
    shader.addUniform(new UniformSpecular("specular"));
    shader.addUniform(new UniformSampler("texture"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformSLights("spotLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.addUniform(new UniformFog("fog"));
    shader.storeUniformLocations();
}

void EntityRenderer::preRender(TransMat &, Scene* ) {


}

void EntityRenderer::render(TransMat &matrices, Scene *scene) {
    GLUtil::enableDepthTesting(true);
    shader.start();
    loadSpotLights(scene);
    loadPointLights(scene);
    loadDirectionalLight(scene);
    loadCamPosition(scene);
    shader.getUniform<UniformFog>("fog")->load(scene->getFog());
    shader.getUniform<UniformSampler>("texture")->loadTexUnit(1);
    shader.getUniform<UniformVec3>("ambientLight")->load(scene->getAmbient());
    for(auto e : scene->getEntities().withComponents<Model, Position, Rotation, Scale>()) {
        Model* m = e.getComponent<Model>();
        const Position* p = e.getComponent<Position>();
        const Rotation* r = e.getComponent<Rotation>();
        const Scale* s = e.getComponent<Scale>();

        loadMatrices(matrices, p, r, s);
        loadExposion(e);
        m->getVao()->bind(0,1,2);
        bindTexture(m);
        glDrawElements(GL_TRIANGLES, m->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        unbindTexture();
        m->getVao()->unbind(0,1,2);
    }
    shader.stop();
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


void EntityRenderer::bindTexture(const Model* m) {
    shader.getUniform<UniformSpecular>("specular")->load(m->specularPower, m->reflectance);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m->getTexture());
}

void EntityRenderer::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
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

void EntityRenderer::loadExposion(Entity &e) {
    if(e.hasComponent<Explode>()) {
        Explode* ex = e.getComponent<Explode>();
        shader.getUniform<UniformFloat>("explodeDistance")->load(ex->interpolated);
        shader.getUniform<UniformFloat>("explodeActive")->load(ex->active);
    }
    else {
        shader.getUniform<UniformFloat>("explodeDistance")->load(0.0f);
        shader.getUniform<UniformFloat>("explodeActive")->load(0.0f);
    }
}

void EntityRenderer::loadPointLights(Scene *scene) {
    unsigned counter = 0;
    for(auto light : scene->getEntities().withComponents<PointLight, Position>()) {
        PointLight* pl = light.getComponent<PointLight>();
        Position* p = light.getComponent<Position>();
        shader.getUniform<UniformPLights>("pointLight")->load(*pl, p->interpolated, counter);
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
        Position* p = light.getComponent<Position>();
        LookAt* look = light.getComponent<LookAt>();
        shader.getUniform<UniformSLights>("spotLight")->load(*pl,
                                                             p->interpolated,
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
