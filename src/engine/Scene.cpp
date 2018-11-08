#include "Scene.h"

#include <iostream>

#include "../factory/TextureFactory.h"
#include "../factory/VaoFactory.h"
#include "../factory/ModelLoader.h"

Scene::Scene() {
    mod = new ModelComponent("models/cube.obj");
    mat = new MaterialComponent("texture/grassy3.png");
    tran = new TransformComponent(  glm::vec3(0.0f, 0.0f, -1.0f),
                                    glm::vec3(0.0f),
                                    glm::vec3(1));
    Factory::ModelData data;
    if(!Factory::loadOBJ(mod->source, data)) {
        fprintf(stderr, "Could not load object\n");
        exit(-1);
    }
    mod->vao = Factory::VAO->createVao(data.vertices, data.indices, data.textures);
    mat->id = Factory::TEXTURE->createTexture(mat->source);
    camera.velocity.speed = 0.5f;
    camera.view.position = glm::vec3(0.0,0.0,-2.0f);
}

Scene::~Scene() {
    delete mod;
    delete mat;
    delete tran;
}

Camera& Scene::getCamera() {
    return camera;
}
