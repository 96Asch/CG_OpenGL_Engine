#include "Scene.h"
#include "../graphic/mesh/Mesh.h"


Scene::Scene() {
    Mesh mesh;
    mod = new ModelComponent("");
    mat = new MaterialComponent("texture/grassy3.png");
    tran = new TransformComponent(  glm::vec3(0.0f, 0.0f, -1.0f),
                                    glm::vec3(0.0f, 0.0,45.0),
                                    glm::vec3(1));
    mod->vao = v.createVao(mesh.position, mesh.indices, mesh.texture);
    mat->id = t.createTexture(mat->source);
}

Scene::~Scene() {
    delete mod;
    delete mat;
    delete tran;
}

Camera& Scene::getCamera() {
    return camera;
}
