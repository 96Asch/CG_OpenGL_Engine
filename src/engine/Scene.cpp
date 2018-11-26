#include "Scene.h"
#include "Global.h"
#include <iostream>

Scene::Scene() {}

Scene::~Scene() {

}

void Scene::serialize(std::ofstream &) {}

bool Scene::deserialize(std::ifstream &stream) {
    bool success(true);
    std::string buffer;
    stream >> std::ws;
    while(std::getline(stream, buffer)) {
        std::stringstream ss(buffer);
        if(buffer == "[entity]")
            success &= ef.deserialize(stream);
        stream >> std::ws;
    }
    return success;
}

EntityFactory& Scene::getEntities() {
    return ef;
}
