#include "Scene.h"

#include <iostream>

#include "../factory/TextureFactory.h"
#include "../factory/VaoFactory.h"
#include "../factory/ModelLoader.h"
#include "../factory/EntityFactory.h"

Scene::Scene() {

    std::cout << ef.createEntity("models/dragon.obj") << std::endl;

}

Scene::~Scene() {

}

Entity Scene::getEntity(const uint64_t &id) {
    return ef.getEntity(id);
}

EntityFactory& Scene::getEntities() {
    return ef;
}

Camera& Scene::getCamera() {
    return camera;
}
