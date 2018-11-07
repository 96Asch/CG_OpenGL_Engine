#include "InputSystem.h"
#include "../engine/Scene.h"
#include "Global.h"
#include <iostream>

InputSystem::InputSystem() : System() {}

InputSystem::~InputSystem() {}


void InputSystem::init() {
    input = owner->getInputHandler();
}

void InputSystem::update(Scene* scene) {
    scene->getCamera().velocity.velocity = glm::vec3(0.0f);
    if(input->hasInput()) {
        handleKeys( scene);
    }
}

void InputSystem::cleanup() {
    input = nullptr;
}

void InputSystem::handleKeys(Scene* scene) {
    glm::vec3 increase;
    if(input->isKeyRepeated(SDLK_w)) {
        increase = glm::vec3(0.0f,0.0f,-1.0f);
    }
    if(input->isKeyRepeated(SDLK_a)){
        increase = glm::vec3(1.0f,0.0f,0.0f);
    }
    if(input->isKeyRepeated(SDLK_s)){
        increase = glm::vec3(0.0f,0.0f,-1.0f);
    }
    if(input->isKeyRepeated(SDLK_d)){
        increase = glm::vec3(1.0f,0.0f,0.0f);
    }
    if(input->isKeyRepeated(SDLK_q)){
        increase = glm::vec3(0.0f,-1.0f,0.0f);
    }
    if(input->isKeyRepeated(SDLK_e)){
        increase = glm::vec3(0.0f,1.0f,0.0f);
    }

    scene->getCamera().velocity.velocity = increase;
    scene->getCamera().view.position += increase;
    // scene->getCamera().view.target += increase;
}
