#include <glm/mat4x4.hpp>

#include "EntityLightRenderer.h"
#include "../../factory/FboFactory.h"
#include "../globjects/GBuffer.h"
#include "Uniforms.h"
#include "Global.h"
#include "Components.h"
#include "../../engine/Scene.h"

EntityLightRenderer::EntityLightRenderer() {}

EntityLightRenderer::~EntityLightRenderer() {}

void EntityLightRenderer::init() {
    shader.init("shader/entity-light.vs", "shader/entity-light.fs",
                {"position", "uv"});
    shader.addUniform(new UniformVec3("ambientLight"));
    shader.addUniform(new UniformVec3("camPosition"));
    shader.addUniform(new UniformInt("gPosition"));
    shader.addUniform(new UniformInt("gNormal"));
    shader.addUniform(new UniformInt("gAlbedoSpec"));
    shader.addUniform(new UniformPLights("pointLight"));
    shader.addUniform(new UniformSLights("spotLight"));
    shader.addUniform(new UniformDLight("directionalLight"));
    shader.storeUniformLocations();

    shader.start();
    shader.getUniform<UniformInt>("gPosition")->load(0);
    shader.getUniform<UniformInt>("gNormal")->load(1);
    shader.getUniform<UniformInt>("gAlbedoSpec")->load(2);
    shader.stop();
    Factory::generateQuad("screenQuad", 1.0f);
}

void EntityLightRenderer::render(TransMat &matrices, std::shared_ptr<Scene> scene) {
    shader.start();
    loadSpotLights(scene);
    loadPointLights(scene);
    loadDirectionalLight(scene);
    loadCamPosition(scene);
    shader.getUniform<UniformVec3>("ambientLight")->load(scene->getAmbient());
    auto vao = Factory::VAO->getVao("screenQuad");
    vao->bind();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, vao->getVertexCount());
    vao->unbind();
    shader.stop();
};

void EntityLightRenderer::cleanup() {
    shader.cleanup();
}

void EntityLightRenderer::loadCamPosition(std::shared_ptr<Scene> scene) {
    glm::vec3 position(glm::vec3(0.0f));
    for(auto e : scene->getEntities().withComponents<Camera, Position>()) {
        position = e.getComponent<Position>()->interpolated;
    }
    shader.getUniform<UniformVec3>("camPosition")->load(position);
}

void EntityLightRenderer::loadPointLights(std::shared_ptr<Scene> scene) {
    unsigned counter = 0;
    for(auto light : scene->getEntities().withComponents<PointLight, Position>()) {
        PointLight* pl = light.getComponent<PointLight>();
        Position* p = light.getComponent<Position>();
        shader.getUniform<UniformPLights>("pointLight")->load(*pl, p->interpolated, counter);
        ++counter;
    }
    while(counter < Global::MAX_POINT_LIGHTS) {
        shader.getUniform<UniformPLights>("pointLight")->loadEmpty(counter);
        ++counter;
    }
}

void EntityLightRenderer::loadSpotLights(std::shared_ptr<Scene> scene) {
    unsigned counter = 0;
    for(auto light : scene->getEntities().withComponents<SpotLight, Position, LookAt>()) {
        SpotLight* pl = light.getComponent<SpotLight>();
        Position* p = light.getComponent<Position>();
        LookAt* look = light.getComponent<LookAt>();
        shader.getUniform<UniformSLights>("spotLight")->load(*pl,
                                                             p->interpolated,
                                                             look->interpolated,
                                                             counter);
        ++counter;
    }
    while(counter < Global::MAX_SPOT_LIGHTS) {
        shader.getUniform<UniformSLights>("spotLight")->loadEmpty(counter);
        ++counter;
    }
}

void EntityLightRenderer::loadDirectionalLight(std::shared_ptr<Scene> scene) {
    shader.getUniform<UniformDLight>("directionalLight")->load(scene->getDirectional());
}
