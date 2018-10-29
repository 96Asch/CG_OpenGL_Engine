#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EntityRenderer.h"
#include "Uniforms.h"
#include "../mesh/Mesh.h"
#include "../../engine/Camera.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    Mesh mesh;
    mod = new ModelComponent("");
    mat = new MaterialComponent("texture/grassy3.png");
    tran = new TransformComponent(  glm::vec3(0.0f),
                                    glm::vec3(0.0f, 0.0,45.0),
                                    glm::vec3(1));
    mod->vao = v.createVao(mesh.position, 12, mesh.indices, 6, mesh.texture, 8);
    mat->id = t.createTexture("texture/grassy3.png");

    buildProjectionMatrix();

    shader.init("shader/entity", "position", "texture");
    shader.addUniform("modelMatrix", new UniformMat4("model"));
    shader.addUniform("projectionMatrix", new UniformMat4("projection"));
    shader.storeUniformLocations();
    shader.start();
    shader.getUniform<UniformMat4>("projectionMatrix")->load(projection);
    shader.stop();
}

void EntityRenderer::preRender() {
    shader.start();
    tran->rotation.z += 0.02f;
    tran->position.z -= 0.001f;
}

void EntityRenderer::render() {
    preRender();

    mod->vao->bind(0,1);
    buildModelMatrix(tran);
    shader.getUniform<UniformMat4>("modelMatrix")->load(model);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mat->id);
    glDrawElements(GL_TRIANGLES, mod->vao->getIndexCount(), GL_UNSIGNED_INT, 0);
    mod->vao->unbind(0,1);

    postRender();
};

void EntityRenderer::postRender() {
    shader.stop();
}

void EntityRenderer::cleanup() {
    shader.cleanup();
    delete mod;
    delete mat;
    delete tran;
}

void EntityRenderer::buildModelMatrix(const TransformComponent* transform) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, transform->position);
    model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0,0,1));
    model = glm::scale(model, transform->scale);
}

void EntityRenderer::buildViewMatrix(const Camera &camera) {
    view = glm::lookAt(
                        camera.position,
                        camera.target,
                        camera.up
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
