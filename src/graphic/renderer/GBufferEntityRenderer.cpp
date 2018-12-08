#include <glm/mat4x4.hpp>

#include "GBufferEntityRenderer.h"
#include "../../factory/FboFactory.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

GBufferEntityRenderer::GBufferEntityRenderer() {}

GBufferEntityRenderer::~GBufferEntityRenderer() {}

void GBufferEntityRenderer::init() {
    shader.init("shader/entity-gbuffer.vs", "shader/entity-gbuffer.fs",
                "shader/entity-gbuffer.gs",
                {"position", "uv", "normal"});
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformInt("texDiffuse"));
    shader.addUniform(new UniformInt("texSpecular"));
    shader.addUniform(new UniformFloat("explodeDistance"));
    shader.addUniform(new UniformFloat("explodeActive"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformInt>("texDiffuse")->load(0);
    shader.getUniform<UniformInt>("texSpecular")->load(1);
    shader.stop();
}

void GBufferEntityRenderer::render(TransMat &matrices, std::shared_ptr<Scene> scene) {
    shader.start();
    for(auto e : scene->getEntities().withComponents<Model, Position, Rotation, Scale>()) {
        Model* m = e.getComponent<Model>();
        const Position* p = e.getComponent<Position>();
        const Rotation* r = e.getComponent<Rotation>();
        const Scale* s = e.getComponent<Scale>();
        loadMatrices(matrices, p, r, s);
        loadExposion(e);
        m->getVao()->bind();
        bindTexture(m);
        glDrawElements(GL_TRIANGLES, m->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        unbindTexture();
        m->getVao()->unbind();
    }
    shader.stop();
};

void GBufferEntityRenderer::cleanup() {
    shader.cleanup();
}

void GBufferEntityRenderer::bindTexture(const Model* m) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m->texture.getDiffuse());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m->texture.getSpecular());
}

void GBufferEntityRenderer::unbindTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}


void GBufferEntityRenderer::loadMatrices(TransMat &mat,
                                  const Position* p,
                                  const Rotation* r,
                                  const Scale* s)
{
    buildModelMatrix(mat.model, p, r ,s);
    shader.getUniform<UniformMat4>("model")->load(mat.model);
    mat.mvp = mat.projection * mat.view * mat.model;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void GBufferEntityRenderer::loadExposion(Entity &e) {
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

void GBufferEntityRenderer::buildModelMatrix(glm::mat4 &model,
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
