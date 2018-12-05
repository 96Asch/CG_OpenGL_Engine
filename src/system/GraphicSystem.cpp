#include <iostream>
#include "GraphicSystem.h"
#include "Renderers.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../factory/FboFactory.h"
#include "../graphic/globjects/ShadowFbo.h"
#include "Components.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    buildProjectionMatrix();
    screenRenderers.push_back(new SkyboxRenderer());
    screenRenderers.push_back(new TerrainRenderer());
    screenRenderers.push_back(new EntityRenderer());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(auto renderer : screenRenderers)
        renderer->init();
        glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GraphicSystem::renderStep(const float &interpolation, Scene* scene) {
    const glm::vec3& color = scene->getFog().color;
    glClearColor(color.x, color.y, color.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    interpolationStep(interpolation, scene);
    buildViewMatrix(scene);
    for(auto renderer : screenRenderers)
        renderer->render(transform, scene);
}

void GraphicSystem::cleanup() {
    for(auto renderer : screenRenderers) {
        renderer->cleanup();
        delete renderer;
    }
}

void GraphicSystem::buildViewMatrix(Scene *scene) {
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

void GraphicSystem::interpolationStep(const float &interpolation, Scene *scene) {
    interpolatePositions(interpolation, scene);
    interpolateRotations(interpolation, scene);
    interpolateScales(interpolation, scene);
    interpolateCamera(interpolation, scene);
    interpolateLookAt(interpolation, scene);
    interpolateExplosions(interpolation, scene);
}

void GraphicSystem::interpolatePositions(const float &interpolation,
                                         Scene *scene)
{
    for(auto e : scene->getEntities().withComponents<Position>()) {
        Position* p = e.getComponent<Position>();
        p->interpolated = Util::lerp(p->lastPosition, p->position, interpolation);
    }
}


void GraphicSystem::interpolateRotations(const float &interpolation,
                                         Scene *scene)
{
    for(auto e : scene->getEntities().withComponents<Rotation>()) {
        Rotation* r = e.getComponent<Rotation>();
        r->interpolated = Util::lerp(r->lastRotation, r->rotation, interpolation);
    }
}

void GraphicSystem::interpolateScales(const float &interpolation,
                                      Scene *scene)
{
    for(auto e : scene->getEntities().withComponents<Scale>()) {
        Scale* s = e.getComponent<Scale>();
        s->interpolated = Util::lerp(s->lastScale, s->scale, interpolation);
    }
}

void GraphicSystem::interpolateExplosions(const float &interpolation,
                                          Scene *scene)
{
    for(auto e : scene->getEntities().withComponents<Explode>()) {
        Explode* ex = e.getComponent<Explode>();
        ex->interpolated = Util::lerp(ex->lastDistance, ex->distance, interpolation);
    }
}

void GraphicSystem::interpolateLookAt(const float &interpolation,
                                      Scene *scene)
{
    for(auto e : scene->getEntities().withComponents<LookAt>()) {
        LookAt* l = e.getComponent<LookAt>();
        l->interpolated = Util::lerp(l->lastDirection, l->direction, interpolation);
    }
}

void GraphicSystem::interpolateCamera(const float &interpolation,
                                      Scene* scene)
{
    for(auto e : scene->getEntities().withComponents<Camera>()) {
        Camera* c = e.getComponent<Camera>();
        c->interpolatedUp = Util::lerp(c->lastUp, c->up, interpolation);
    }
}
