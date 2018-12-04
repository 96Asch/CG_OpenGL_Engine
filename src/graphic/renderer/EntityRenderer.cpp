#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <vector>

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
    shader.addUniform(new UniformMat4("mv"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformMaterial("material"));
    shader.addUniform(new UniformSampler("texture"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.addUniform(new UniformFog("fog"));
    shader.storeUniformLocations();
}

void EntityRenderer::preRender(const float &,
                               TransMat &mat,
                               Scene* scene) {
    GLUtil::cullBackFaces(true);
    shader.start();
    loadPointLights(mat.view, scene);
    loadDirectionalLight(mat.view, scene);
    shader.getUniform<UniformFog>("fog")->load(scene->getFog());
    shader.getUniform<UniformSampler>("texture")->loadTexUnit(0);
}

void EntityRenderer::render(const float &interpolation,
                            TransMat &mat,
                            Scene *scene) {
    preRender(interpolation, mat, scene);

    for(auto e : scene->getEntities().withComponents<Model, Material, Position, Rotation, Scale>()) {
        Model* model = e.getComponent<Model>();
        Material* material = e.getComponent<Material>();
        Position* pos = e.getComponent<Position>();
        Rotation* rot = e.getComponent<Rotation>();
        Scale* sca = e.getComponent<Scale>();

        buildModelMatrix(mat.model, pos, rot, sca, interpolation);
        shader.getUniform<UniformMaterial>("material")->load(*material);
        loadMatrices(mat);
        model->getVao()->bind(0,1,2);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, material->id);
        glDrawElements(GL_TRIANGLES, model->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        model->getVao()->unbind(0,1,2);
    }
    postRender(interpolation, scene);
};

void EntityRenderer::postRender(const float &, Scene*) {
    shader.stop();
    GLUtil::cullBackFaces(false);
}

void EntityRenderer::cleanup() {
    shader.cleanup();
}

void EntityRenderer::loadMatrices(TransMat &mat) {
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mv = mat.view * mat.model;
    shader.getUniform<UniformMat4>("mv")->load(mat.mv);
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void EntityRenderer::loadPointLights(const glm::mat4 &view, Scene *scene) {
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

void EntityRenderer::loadDirectionalLight(const glm::mat4 &view, Scene *scene) {
    shader.getUniform<UniformDLight>("directionalLight")->load(scene->getDirectional());
}

void EntityRenderer::buildModelMatrix(glm::mat4 &model,
                                      const Position* p,
                                      const Rotation* r,
                                      const Scale* s,
                                      const float &interpolation)
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, p->interpolated);
    model = glm::rotate(model, glm::radians(r->interpolated.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(r->interpolated.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(r->interpolated.z), glm::vec3(0,0,1));
    model = glm::scale(model, s->interpolated);
}
