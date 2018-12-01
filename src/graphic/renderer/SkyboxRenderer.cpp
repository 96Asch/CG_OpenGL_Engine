#include "SkyboxRenderer.h"
#include "Uniforms.h"
#include "Global.h"
#include "../../engine/Scene.h"
#include "../../environment/Skybox.h"

SkyboxRenderer::SkyboxRenderer() {

}

SkyboxRenderer::~SkyboxRenderer() {

}

void SkyboxRenderer::init() {
    shader.init("shader/skybox", "position");
    shader.addUniform(new UniformMat4("pv"));
    shader.addUniform(new UniformSampler("map1"));
    shader.addUniform(new UniformVec3("fogColor"));
    shader.storeUniformLocations();
}

void SkyboxRenderer::preRender(const float &,
                               TransMat &,
                               Scene *)
{
    GLUtil::enableDepthMask(false);
    shader.start();
}

void SkyboxRenderer::render(const float &interpolation,
                            TransMat &mat,
                            Scene* scene)
{
    Skybox &box = scene->getSky();
    if(box.active) {
        preRender(interpolation, mat, scene);
        buildProjectionViewMatrix(mat, box);
        shader.getUniform<UniformMat4>("pv")->load(mat.pv);
        shader.getUniform<UniformSampler>("map1")->loadTexUnit(0);
        shader.getUniform<UniformVec3>("fogColor")->load(scene->getFog().color);

        box.getVao()->bind(0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, box.texture);
        glDrawElements(GL_TRIANGLES, box.getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        box.getVao()->unbind(0);

        postRender(interpolation, scene);
    }
}

void SkyboxRenderer::postRender(const float &, Scene *) {
    shader.stop();
    GLUtil::enableDepthMask(true);
}

void SkyboxRenderer::cleanup() {
    shader.cleanup();
};

void SkyboxRenderer::buildProjectionViewMatrix(TransMat &mat, Skybox &box) {
    glm::mat4 v = glm::mat4(mat.view);
    v[3][0] = 0.0f;
    v[3][1] = 0.0f;
    v[3][2] = 0.0f;
    v = glm::rotate(v, glm::radians(box.rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    mat.pv = glm::mat4(mat.projection * v);
}
