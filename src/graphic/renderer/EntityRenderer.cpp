#include <glm/mat4x4.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
#include "Components.h"
#include "Global.h"
#include "../../engine/Scene.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init(const glm::mat4 &projection) {
    shader.init("shader/entity", "position", "texture");
    shader.addUniform("modelMatrix", new UniformMat4("model"));
    shader.addUniform("viewMatrix", new UniformMat4("view"));
    shader.addUniform("projectionMatrix", new UniformMat4("projection"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformMat4>("projectionMatrix")->load(projection);
    shader.stop();
}

void EntityRenderer::preRender(const float &,
                               const glm::mat4 &view,
                               Scene*) {
    shader.start();
    shader.getUniform<UniformMat4>("viewMatrix")->load(view);
}

void EntityRenderer::render(const float &interpolation,
                            const glm::mat4 &view,
                            Scene *scene) {
    preRender(interpolation, view, scene);

    for(auto e : scene->getEntities().withComponents<Model, Transform, Material>()) {

        Model* mod = e.getComponent<Model>();
        Transform* tra = e.getComponent<Transform>();
        Material* mat = e.getComponent<Material>();


        mod->getVao()->bind(0,1);
        shader.getUniform<UniformMat4>("modelMatrix")->load(buildModelMatrix(tra, interpolation));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mat->id);
        glDrawElements(GL_TRIANGLES, mod->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        mod->getVao()->unbind(0,1);
    }
    postRender(interpolation, scene);
};

void EntityRenderer::postRender(const float &, Scene*) {
    shader.stop();
}

void EntityRenderer::cleanup() {
    shader.cleanup();
}

glm::mat4 EntityRenderer::buildModelMatrix(const Transform* t, const float &interpolation) {
    glm::mat4 model = glm::mat4(1.0f);
    glm::vec3 positionInterpol = Util::lerp(t->lastPosition, t->position, interpolation);
    glm::vec3 rotationInterpol = Util::lerp(t->lastRotation, t->rotation, interpolation);
    glm::vec3 scaleInterpol = Util::lerp(t->lastScale, t->scale, interpolation);
    fprintf(stderr, "pos(%f,%f,%f)\n",  t->lastPosition.x, t->lastPosition.y, t->lastPosition.z);
    model = glm::translate(model, positionInterpol);
    model = glm::rotate(model, glm::radians(rotationInterpol.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(rotationInterpol.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(rotationInterpol.z), glm::vec3(0,0,1));
    model = glm::scale(model, scaleInterpol);
    return model;
}
