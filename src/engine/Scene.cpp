#include <iostream>
#include <cstdlib>

#include "Scene.h"
#include "Global.h"
#include "../environment/BaseLight.h"
#include "Components.h"

Scene::Scene() : upDirection(glm::vec3(0.0f, 1.0f, 0.0f)),
                 ambientLight(glm::vec3(0.2f, 0.2f, 0.2f))
{
    srand(9);

 //    for (int i = 0; i < 0; ++i)
 //    {
 //        // float colX = 0.1f * (rand() % 100);
 //        // float colY = 0.1f * (rand() % 100);
 //        // float colZ = 0.1f * (rand() % 100);
 //
 //        float posX = rand() % 25;
 //        float posY = rand() % 5 + 1;
 //        float posZ = rand() % 25;
 //
 //        auto e = ef.createEntity();
 //        ef.addComponent(e.id, PointLight(BaseLight(glm::vec3(1.0f,0.0f,0.0f), 32.0f),
 //                                  glm::vec3(0,0,1),
 //                                  10.0f));
 //        ef.addComponent(e.id, Position(glm::vec3(10, 2, -10)));
 //        std::cout << e << std::endl;
 //    }
 }

Scene::~Scene() {

}

void Scene::serialize(std::ofstream &) {}

bool Scene::deserialize(std::ifstream &stream) {
    bool success(true);
    std::string tag;
    stream >> std::ws;
    while(std::getline(stream, tag)) {
        std::stringstream ss(tag);
        if(tag == "[entity]")
            success &= ef.deserialize(stream);
        else if (tag == "[directionallight]")
            success &= light.deserialize(stream);
        else if (tag == "[skybox]")
            success &= sky.deserialize(stream);
        else if (tag == "[fog]")
            success &= fog.deserialize(stream);
        else if (tag == "[terrain]")
            success &= terrain.deserialize(stream);
        stream >> std::ws;
    }
    return success;
}

EntityFactory& Scene::getEntities() {
    return ef;
}

DirectionalLight& Scene::getDirectional() {
    return light;
}

Fog& Scene::getFog() {
    return fog;
}

Terrain& Scene::getTerrain() {
    return terrain;
}

Skybox& Scene::getSky() {
    return sky;
}

glm::vec3 Scene::getUpDirection() {
    return upDirection;
}

glm::vec3 Scene::getAmbient() {
    return ambientLight;
}
