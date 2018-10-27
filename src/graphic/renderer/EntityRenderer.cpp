#include "EntityRenderer.h"
#include "../uniform/Uniforms.h"

EntityRenderer::EntityRenderer() {}

EntityRenderer::~EntityRenderer() {}

void EntityRenderer::init() {
    Mesh m;
    vao = v.createVao(m.position, 12, m.indices, 6, m.texture, 8);
    tex = t.createTexture("grassy3.png");
    shader.init("shader/entity", "position", "texture");
    shader.storeUniformLocations();
}

void EntityRenderer::preRender() {
    shader.start();
}

void EntityRenderer::render() {
    preRender();

    vao->bind(0,1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glDrawElements(GL_TRIANGLES, vao->getIndexCount(), GL_UNSIGNED_INT, 0);
    vao->unbind(0,1);

    postRender();
}

void EntityRenderer::postRender() {
    shader.stop();
}

void EntityRenderer::cleanup() {
    shader.cleanup();
}
