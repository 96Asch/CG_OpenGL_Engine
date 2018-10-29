#include <iostream>
#include "GraphicSystem.h"
#include "Renderers.h"
#include "../engine/Scene.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    renderers.push_back(new EntityRenderer());

    for(auto renderer : renderers)
        renderer->init();
}

void GraphicSystem::update(const float &delta, Scene *scene) {
    render(scene);
}

void GraphicSystem::render(Scene *scene) {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto renderer : renderers)
        renderer->render(scene);
}

void GraphicSystem::cleanup() {
    for(auto renderer : renderers) {
        renderer->cleanup();
        delete renderer;
    }
}
