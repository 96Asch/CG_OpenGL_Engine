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
    mesh->vao->createAttribute(0, 3, mesh->g_vertex_buffer_data, 9);
    mesh->vao->unbind();
}

void GraphicSystem::update(const float &delta) {
    render();
}

void GraphicSystem::render() {
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    mesh->vao->bind(0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    mesh->vao->unbind(0);
}

void GraphicSystem::cleanup() {
    mesh->vao->remove();
    delete mesh->vao;
    delete mesh;
}
