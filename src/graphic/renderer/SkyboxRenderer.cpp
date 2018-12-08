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
    shader.init("shader/skybox.vs", "shader/skybox.fs", {"position"});
    shader.addUniform(new UniformMat4("pv"));
    shader.addUniform(new UniformInt("map1"));
    shader.addUniform(new UniformVec3("fogColor"));
    shader.storeUniformLocations();
}

void SkyboxRenderer::render(TransMat &mat,
                            const std::shared_ptr<Scene> &scene)
{
    Skybox &box = scene->getSky();
    if(box.active) {
        GLUtil::cullFrontFaces(true);
        GLUtil::enableDepthMask(false);
        shader.start();

        buildProjectionViewMatrix(mat, box);
        shader.getUniform<UniformMat4>("pv")->load(mat.pv);
        shader.getUniform<UniformInt>("map1")->load(0);
        shader.getUniform<UniformVec3>("fogColor")->load(scene->getFog().color);

        box.getVao()->bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, box.getTexture());
        glDrawElements(GL_TRIANGLES, box.getVao()->getIndexCount(), GL_UNSIGNED_INT, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        box.getVao()->unbind();

        shader.stop();
        GLUtil::cullFrontFaces(false);
        GLUtil::enableDepthMask(true);
    }
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
