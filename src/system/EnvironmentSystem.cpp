#include "EnvironmentSystem.h"
#include "../engine/Scene.h"
#include "../environment/DirectionalLight.h"
#include "../environment/Fog.h"
#include "../environment/Skybox.h"

EnvironmentSystem::EnvironmentSystem() {

}

EnvironmentSystem::~EnvironmentSystem() {

}

void EnvironmentSystem::init() {

}

void EnvironmentSystem::update(const float &tps, Scene* scene) {
    updateSky(tps, scene->getSky());
    updateDirectionalLight(tps, scene->getDirectional(), scene->getSky().rotation);
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
