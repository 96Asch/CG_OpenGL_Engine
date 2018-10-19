#include "GraphicSystem.h"
#include <iostream>

GraphicSystem::GraphicSystem() : System(){

}

GraphicSystem::~GraphicSystem(){}


void GraphicSystem::init() {
    printf("%s\n", "init");
    mesh = new FlatMesh;
    mesh->vao = Vao::create();
    mesh->vao->bind();
    mesh->vao->createIndexBuffer(mesh->QUAD_INDICES, 6);
    mesh->vao->createAttribute(0, 2, mesh->QUAD_POSITIONS, 8);
    mesh->vao->unbind();
}

void GraphicSystem::update(const float &delta) {
    render();
}

void GraphicSystem::render() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicSystem::cleanup() {
    mesh->vao->remove();
    delete mesh->vao;
    delete mesh;
}
