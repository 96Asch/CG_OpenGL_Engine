#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
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
    Entity entity = scene->getEntity(1);

    // scene->mod->vao->bind(0,1);
    // buildModelMatrix(scene->tran);
    // shader.getUniform<UniformMat4>("modelMatrix")->load(model);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, scene->mat->id);
    // glDrawElements(GL_TRIANGLES, scene->mod->vao->getIndexCount(), GL_UNSIGNED_INT, 0);
    // scene->mod->vao->unbind(0,1);

    postRender(interpolation, scene);
};

void EntityRenderer::postRender(const float &, Scene*) {
    shader.stop();
}

void EntityRenderer::cleanup() {
    shader.cleanup();
}

void EntityRenderer::buildModelMatrix(const TransformComponent* transform) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, transform->position);
    model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0,0,1));
    model = glm::scale(model, transform->scale);
}
