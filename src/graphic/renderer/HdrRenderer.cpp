#include <glm/mat4x4.hpp>

#include "HdrRenderer.h"
#include "../../factory/FboFactory.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

HdrRenderer::HdrRenderer() {}

HdrRenderer::~HdrRenderer() {}

void HdrRenderer::init() {
    shader.init("shader/quad.vs", "shader/hdr.fs",
                {"position"});
    shader.addUniform(new UniformInt("colorTex"));
    shader.addUniform(new UniformInt("brightTex"));
    shader.addUniform(new UniformFloat("exposure"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformInt>("colorTex")->load(0);
    shader.getUniform<UniformInt>("brightTex")->load(1);
    shader.stop();
    Factory::generateQuad("screenQuad", 1.0f);
}

void HdrRenderer::render(TransMat &,
                         const std::shared_ptr<Scene> &scene)
{
    shader.start();
    shader.getUniform<UniformFloat>("exposure")->load(scene->getExposure());
    auto vao = Factory::VAO->getVao("screenQuad");
    vao->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vao->getVertexCount());
    vao->unbind();
    shader.stop();
};

void HdrRenderer::cleanup() {
    shader.cleanup();
}
