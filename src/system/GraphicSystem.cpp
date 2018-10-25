#include <iostream>
#include "GraphicSystem.h"
#include "../graphic/renderer/Renderers.h"

GraphicSystem::GraphicSystem() : System() {}

GraphicSystem::~GraphicSystem(){}

void GraphicSystem::init() {
    printf("%s\n", "init");
    renderers.push_back(new EntityRenderer());

    for(auto renderer : renderers)
        renderer->init();
}

void GraphicSystem::update(const float &delta) {
    render();
}

void GraphicSystem::render() {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto renderer : renderers)
        renderer->render();
}

void GraphicSystem::cleanup() {
    for(auto renderer : renderers) {
        renderer->cleanup();
        delete renderer;
    }
}
