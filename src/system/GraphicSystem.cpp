#include <iostream>
#include "GraphicSystem.h"
#include "Renderers.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    renderers.push_back(new EntityRenderer());
    buildProjectionMatrix();

    for(auto renderer : renderers)
        renderer->init(projection);

    GLUtil::enableDepthTesting(true);
}

void GraphicSystem::render(const float &interpolation, Scene* scene) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    buildViewMatrix(interpolation, scene->getCamera());

    for(auto renderer : renderers)
        renderer->render(interpolation, view, scene);
}

void GraphicSystem::cleanup() {
    for(auto renderer : renderers) {
        renderer->cleanup();
        delete renderer;
    }
}

void GraphicSystem::buildViewMatrix(const float &interpolation,
                                     const Camera &camera) {
    glm::vec3 positionInterpol = lerp(camera.lastPosition,
                                      camera.position,
                                      interpolation);
    glm::vec3 targetInterpol = lerp(camera.lastTarget,
                                    camera.target,
                                    interpolation);
    glm::vec3 upInterpol = lerp(camera.lastUp,
                                camera.up,
                                interpolation);
    view = glm::lookAt(
                        positionInterpol,
                        positionInterpol + targetInterpol,
                        upInterpol
                      );
}

void GraphicSystem::buildProjectionMatrix() {
    projection = glm::perspective(
                                    glm::radians(Global::fov),
                                    Global::aspectRatio,
                                    Global::nearPlane,
                                    Global::farPlane
                                 );
}
