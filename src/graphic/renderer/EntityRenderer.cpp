#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
#include "../../engine/Scene.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    buildProjectionMatrix();

    shader.init("shader/entity", "position", "texture");
    shader.addUniform("modelMatrix", new UniformMat4("model"));
    shader.addUniform("viewMatrix", new UniformMat4("view"));
    shader.addUniform("projectionMatrix", new UniformMat4("projection"));
    shader.storeUniformLocations();
    shader.start();
    shader.getUniform<UniformMat4>("projectionMatrix")->load(projection);
    shader.stop();
}

void EntityRenderer::preRender(const float &interpolation, Scene* scene) {
    shader.start();
    buildViewMatrix(interpolation, scene->getCamera());
    shader.getUniform<UniformMat4>("viewMatrix")->load(view);
}

void EntityRenderer::render(const float &interpolation, Scene* scene) {
    preRender(interpolation, scene);

    scene->mod->vao->bind(0,1);
    buildModelMatrix(scene->tran);
    shader.getUniform<UniformMat4>("modelMatrix")->load(model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, scene->mat->id);
    glDrawElements(GL_TRIANGLES, scene->mod->vao->getIndexCount(), GL_UNSIGNED_INT, 0);
    scene->mod->vao->unbind(0,1);

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

void EntityRenderer::buildViewMatrix(const float &interpolation,
                                     const Camera &camera) {
    glm::vec3 positionInterpol = lerp(camera.view.lastPosition,
                                      camera.view.position,
                                      interpolation);
    view = glm::lookAt(
                        positionInterpol,
                        positionInterpol + camera.view.target,
                        camera.view.up
                      );
}

void EntityRenderer::buildProjectionMatrix() {
    projection = glm::perspective(
                                    glm::radians(Global::fov),
                                    Global::aspectRatio,
                                    Global::nearPlane,
                                    Global::farPlane
                                 );
}
