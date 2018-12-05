#include <glm/mat4x4.hpp>

#include "ShadowRenderer.h"
#include "Global.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"
#include "../../factory/FboFactory.h"
#include "../globjects/ShadowFbo.h"

ShadowRenderer::ShadowRenderer() {

}

ShadowRenderer::~ShadowRenderer() {

}

void ShadowRenderer::init() {
    Factory::FBO->createFbo<ShadowFbo>("shadow")->init(Global::width, Global::height);
    shader.init("shader/shadow", "position", "uv", "normal");
    shader.addUniform(new UniformMat4("mvp"));
    shader.addUniform(new UniformSampler("shadowMap"));
    shader.storeUniformLocations();
}

void ShadowRenderer::render(TransMat &t, Scene *scene) {
    glClear(GL_DEPTH_BUFFER_BIT);
    auto shadowFbo = std::static_pointer_cast<ShadowFbo>(Factory::FBO->getFbo("shadow"));
    shadowFbo->bindForWriting();
    shader.start();
    GLUtil::cullBackFaces(true);
    GLUtil::enableDepthTesting(true);
    for(auto e : scene->getEntities().withComponents<Model, Position, Rotation, Scale>()) {
        Model* mod = e.getComponent<Model>();
        const Position* pos = e.getComponent<Position>();
        const Rotation* rot = e.getComponent<Rotation>();
        const Scale* sca = e.getComponent<Scale>();

        loadMVP(t, pos, rot, sca);

        mod->getVao()->bind(0);
        glDrawElements(GL_TRIANGLES, mod->getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        mod->getVao()->unbind(0);
    }
    GLUtil::cullBackFaces(false);
    GLUtil::enableDepthTesting(false);
    shader.stop();
    shadowFbo->unbind();
}

void ShadowRenderer::cleanup() {
    shader.cleanup();
}

void ShadowRenderer::preRender(TransMat &, Scene *) {

}

void ShadowRenderer::postRender(Scene *) {

}

void ShadowRenderer::loadMVP(TransMat &mat,
                                  const Position* p,
                                  const Rotation* r,
                                  const Scale* s)
{
    buildModelMatrix(mat.model, p, r ,s);
    mat.mv = mat.view * mat.model;
    mat.mvp = mat.projection * mat.mv;
    shader.getUniform<UniformMat4>("mvp")->load(mat.mvp);
}

void ShadowRenderer::buildModelMatrix(glm::mat4 &model,
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
