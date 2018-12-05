#include "EnvironmentSystem.h"
#include "../engine/Scene.h"
#include "../environment/DirectionalLight.h"
#include "../environment/Fog.h"
#include "../environment/Skybox.h"
#include "Components.h"

EnvironmentSystem::EnvironmentSystem() {

}

EnvironmentSystem::~EnvironmentSystem() {

}

void EnvironmentSystem::init() {

}

void EnvironmentSystem::updateStep(const float &tps, Scene* scene) {
    updateDirectionalLight(tps, scene->getDirectional(), scene->getSky().rotation);
    updateSky(tps, scene->getSky());
    updateExplosions(tps, scene);
}

void EnvironmentSystem::cleanup() {

}

void EnvironmentSystem::updateSky(const float &tps, Skybox &box) {
    box.rotation += box.rotationSpeed * tps;
}

void EnvironmentSystem::updateDirectionalLight(const float &tps,
                                               DirectionalLight &light,
                                               const float &angle)
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),
                                     glm::radians(angle * tps),
                                     glm::vec3(0.0f, 1.0f, 0.0f));
    glm::vec4 direction = glm::vec4(light.direction, 1.0f);
    light.direction = glm::normalize(rotation * direction);
}


void EnvironmentSystem::updateExplosions(const float &tps, Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Explode>()) {
        Explode* ex = e.getComponent<Explode>();
        if(ex->active) {
            ex->lastDistance = ex->distance;
            ex->distance += ex->speed * tps;
        }
        if(ex->distance > 20.0f) {
            std::cout << "destroyed: " << e  << std::endl;
            e.destroy();
        }
    }
}
