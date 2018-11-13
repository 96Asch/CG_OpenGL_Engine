#include "Scene.h"

#include <iostream>

#include "../factory/TextureFactory.h"
#include "../factory/VaoFactory.h"
#include "../factory/ModelLoader.h"


Scene::Scene() : ef(&cm) {

    ef.createEntity("models/cube.obj");
    ef.createEntity("models/barrel.obj");

}

Scene::~Scene() {

}

Entity Scene::getEntity(const uint64_t &id) {
    return ef.getEntity(id);
}

ComponentManager* Scene::getComponentManager() {
    return &cm;
}

Camera& Scene::getCamera() {
    return camera;
}
