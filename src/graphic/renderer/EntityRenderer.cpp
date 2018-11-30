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
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.addUniform(new UniformFog("fog"));
    shader.storeUniformLocations();
}

void EntityRenderer::preRender(const float &,
                               const glm::mat4 &view,
                               const glm::mat4&,
                               Scene* scene) {
    GLUtil::cullBackFaces(true);
    shader.start();
    loadPointLights(view, scene);
    loadDirectionalLight(view, scene);
    shader.getUniform<UniformFog>("fog")->load(scene->getFog());
}

void EntityRenderer::render(const float &interpolation,
                            const glm::mat4 &view,
                            const glm::mat4 &projection,
                            Scene *scene) {
    preRender(interpolation, view, projection, scene);

    for(auto e : scene->getEntities().withComponents<Model, Transform, Material>()) {

        Model* mod = e.getComponent<Model>();
        Transform* tra = e.getComponent<Transform>();
        Material* mat = e.getComponent<Material>();

        mod->getVao()->bind(0,1,2);
        shader.getUniform<UniformMaterial>("material")->load(*mat);
        glm::mat4 model;
        buildModelMatrix(model, tra, interpolation);
        shader.getUniform<UniformMat4>("model")->load(model);
        glm::mat4 mv = view * model;
        shader.getUniform<UniformMat4>("mv")->load(mv);
        glm::mat4 mvp = projection * mv;
        shader.getUniform<UniformMat4>("mvp")->load(mvp);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mat->id);
        glDrawElements(GL_TRIANGLES, mod->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        mod->getVao()->unbind(0,1,2);
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

void EntityRenderer::loadPointLights(const glm::mat4 &view, Scene *scene) {
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

void EntityRenderer::loadDirectionalLight(const glm::mat4 &view, Scene *scene) {
    DirectionalLight light = scene->getDirectional();
    glm::vec4 aux = glm::vec4(light.direction, 0);
    aux = view * aux;
    light.direction = glm::vec3(aux.x, aux.y, aux.z);
    shader.getUniform<UniformDLight>("directionalLight")->load(light);
}

void EntityRenderer::buildModelMatrix(glm::mat4 &model, const Transform* t, const float &interpolation) {
    model = glm::mat4(1.0f);
    glm::vec3 positionInterpol = Util::lerp(t->lastPosition, t->position, interpolation);
    glm::vec3 rotationInterpol = Util::lerp(t->lastRotation, t->rotation, interpolation);
    glm::vec3 scaleInterpol = Util::lerp(t->lastScale, t->scale, interpolation);
    model = glm::translate(model, positionInterpol);
    model = glm::rotate(model, glm::radians(rotationInterpol.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(rotationInterpol.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(rotationInterpol.z), glm::vec3(0,0,1));
    model = glm::scale(model, scaleInterpol);
}
