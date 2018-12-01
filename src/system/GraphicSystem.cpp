#include <iostream>
#include "GraphicSystem.h"
#include "Renderers.h"
#include "Global.h"
#include "../engine/Scene.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    renderers.push_back(new TerrainRenderer());
    renderers.push_back(new SkyboxRenderer());
    renderers.push_back(new EntityRenderer());
    buildProjectionMatrix();

    for(auto renderer : renderers)
        renderer->init();

    GLUtil::enableDepthTesting(true);
}

void GraphicSystem::render(const float &interpolation, Scene* scene) {
    const glm::vec3& color = scene->getFog().color;
    glClearColor(color.x, color.y, color.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    buildViewMatrix(interpolation, scene);

    for(auto renderer : renderers)
        renderer->render(interpolation, transform, scene);
}

void GraphicSystem::cleanup() {
    for(auto renderer : renderers) {
        renderer->cleanup();
        delete renderer;
    }
}

void GraphicSystem::buildViewMatrix(const float &interpolation, Scene *scene) {
    transform.view = glm::mat4(1.0f);
    for (auto e : scene->getEntities().withComponents<Camera>()) {
        Camera* c = e.getComponent<Camera>();
        glm::vec3 positionInterpol = Util::lerp(c->lastPosition,
                                                c->position,
                                                interpolation);
        glm::vec3 targetInterpol = Util::lerp(c->lastTarget,
                                              c->target,
                                              interpolation);
        glm::vec3 upInterpol = Util::lerp(c->lastUp,
                                          c->up,
                                          interpolation);
        transform.view = glm::lookAt(
                                     positionInterpol,
                                     positionInterpol + targetInterpol,
                                     upInterpol
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
