#include <glm/mat4x4.hpp>

#include "GBufferRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

GBufferRenderer::GBufferRenderer() {}

GBufferRenderer::~GBufferRenderer() {}

void GBufferRenderer::init() {
    shader.init("shader/gbuffer.vs", "shader/gbuffer.fs",
                {"position", "uv", "normal"});
    shader.addUniform(new UniformMat4("model"));
    shader.addUniform(new UniformMat4("mvp"));
    shader.storeUniformLocations();
}

void GBufferRenderer::preRender(TransMat &, Scene* ) {


}

void GBufferRenderer::render(TransMat &matrices, Scene *scene) {
    GLUtil::enableDepthTesting(true);
    shader.start();
    shader.stop();
    GLUtil::enableDepthTesting(false);
};

void GBufferRenderer::postRender(Scene*) {

}

void GBufferRenderer::cleanup() {
    shader.cleanup();
}

void GBufferRenderer::buildModelMatrix(glm::mat4 &model,
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
