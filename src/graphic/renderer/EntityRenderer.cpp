#include "EntityRenderer.h"
#include "../uniform/Uniforms.h"

const std::string shaderFile("shader/entity");

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    shader.init(shaderFile, "position");
    shader.addUniform("viewMatrix", new UniformMatrix("view"));

    shader.storeUniformLocations();

    mesh = new FlatMesh;
    mesh->vao = Vao::create();
    mesh->vao->bind();
    mesh->vao->createAttribute(0, 3, mesh->g_vertex_buffer_data, 9);
    mesh->vao->unbind();
}

void EntityRenderer::preRender() {
    shader.start();
    glm::mat4 matrix;
    shader.getUniform<UniformMatrix>("viewMatrix")->load(matrix);
}

void EntityRenderer::render() {
    preRender();

    mesh->vao->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    mesh->vao->unbind(0);

    postRender();
}

void EntityRenderer::postRender() {
    shader.stop();
}

void EntityRenderer::cleanup() {
    shader.cleanup();
    mesh->vao->remove();
    delete mesh->vao;
    delete mesh;
}
