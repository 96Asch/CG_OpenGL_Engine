#include <iostream>
#include "GraphicSystem.h"
#include "Renderers.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../factory/FboFactory.h"
#include "../graphic/globjects/GBuffer.h"
#include "Components.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    buildProjectionMatrix();
    bufferRenderers.push_back(std::make_unique<GBufferTerrainRenderer>());
    bufferRenderers.push_back(std::make_unique<GBufferEntityRenderer>());
    screenRenderers.push_back(std::make_unique<LightRenderer>());
    forwardRenderers.push_back(std::make_unique<SkyboxRenderer>());

    Factory::FBO->createFbo<GBuffer>("GBuffer", Global::width, Global::height);
    for(auto &renderer : bufferRenderers)
        renderer->init();

    for(auto &renderer : screenRenderers)
        renderer->init();

    for(auto &renderer : forwardRenderers)
        renderer->init();
    glEnable(GL_DEPTH_TEST);
}

void GraphicSystem::renderStep(const float &interpolation, std::shared_ptr<Scene> scene) {
    const glm::vec3& color = scene->getFog().color;
    glClearColor(0.0,0.0,0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    interpolationStep(interpolation, scene);
    buildViewMatrix(scene);


    geometryPass(scene);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    lightingPass(scene);
    glClearColor(color.x, color.y, color.z, 1.0);
    forwardPass(scene);
}

void GraphicSystem::cleanup() {
    for(auto &renderer : bufferRenderers) {
        renderer->cleanup();
    }
    for(auto &renderer : screenRenderers) {
        renderer->cleanup();
    }
    for(auto &renderer : forwardRenderers) {
        renderer->cleanup();
    }
}

void GraphicSystem::geometryPass(const std::shared_ptr<Scene> &scene) {
    Factory::FBO->getFbo<GBuffer>("GBuffer")->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto &renderer : bufferRenderers)
        renderer->render(transform, scene);
    Factory::FBO->getFbo<GBuffer>("GBuffer")->unbind();
}

void GraphicSystem::lightingPass(const std::shared_ptr<Scene> &scene) {
    // glEnable(GL_BLEND);
   	// glBlendFunc(GL_ONE, GL_ONE);
    // glDepthMask(false);
    // glDepthFunc(GL_EQUAL);
    Factory::FBO->getFbo<GBuffer>("GBuffer")->bindTextures();
    for(auto &renderer : screenRenderers)
        renderer->render(transform, scene);
    Factory::FBO->getFbo<GBuffer>("GBuffer")->unbindTextures();
    // glDepthFunc(GL_LESS);
    // glDepthMask(true);
    // glDisable(GL_BLEND);
}

void GraphicSystem::forwardPass(const std::shared_ptr<Scene> &scene) {
    Factory::FBO->getFbo<GBuffer>("GBuffer")->blitToDefault(Global::width, Global::height);
    for(auto &renderer : forwardRenderers)
        renderer->render(transform, scene);
}

void GraphicSystem::buildViewMatrix(std::shared_ptr<Scene> scene) {
    transform.view = glm::mat4(1.0f);
    for (auto e : scene->getEntities().withComponents<Camera, Position, LookAt>()) {
        Camera* c = e.getComponent<Camera>();
        Position* p = e.getComponent<Position>();
        LookAt* l = e.getComponent<LookAt>();
        transform.view = glm::lookAt(
                                     p->interpolated,
                                     p->interpolated + l->interpolated,
                                     c->interpolatedUp
                                    );
    }
}

void GraphicSystem::buildProjectionMatrix() {
    transform.projection = glm::perspective(
                                            glm::radians(Global::fov),
                                            Global::aspectRatio,
                                            Global::nearPlane,
                                            Global::farPlane
                                           );
}

void GraphicSystem::interpolationStep(const float &interpolation,
                                      std::shared_ptr<Scene> scene)
{
    interpolatePositions(interpolation, scene);
    interpolateRotations(interpolation, scene);
    interpolateScales(interpolation, scene);
    interpolateCamera(interpolation, scene);
    interpolateLookAt(interpolation, scene);
    interpolateExplosions(interpolation, scene);
}

void GraphicSystem::interpolatePositions(const float &interpolation,
                                         std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<Position>()) {
        Position* p = e.getComponent<Position>();
        p->interpolated = Util::lerp(p->lastPosition, p->position, interpolation);
    }
}


void GraphicSystem::interpolateRotations(const float &interpolation,
                                         std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<Rotation>()) {
        Rotation* r = e.getComponent<Rotation>();
        r->interpolated = Util::lerp(r->lastRotation, r->rotation, interpolation);
    }
}

void GraphicSystem::interpolateScales(const float &interpolation,
                                      std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<Scale>()) {
        Scale* s = e.getComponent<Scale>();
        s->interpolated = Util::lerp(s->lastScale, s->scale, interpolation);
    }
}

void GraphicSystem::interpolateExplosions(const float &interpolation,
                                          std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<Explode>()) {
        Explode* ex = e.getComponent<Explode>();
        ex->interpolated = Util::lerp(ex->lastDistance, ex->distance, interpolation);
    }
}

void GraphicSystem::interpolateLookAt(const float &interpolation,
                                      std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<LookAt>()) {
        LookAt* l = e.getComponent<LookAt>();
        l->interpolated = Util::lerp(l->lastDirection, l->direction, interpolation);
    }
}

void GraphicSystem::interpolateCamera(const float &interpolation,
                                      std::shared_ptr<Scene> scene)
{
    for(auto e : scene->getEntities().withComponents<Camera>()) {
        Camera* c = e.getComponent<Camera>();
        c->interpolatedUp = Util::lerp(c->lastUp, c->up, interpolation);
    }
}
