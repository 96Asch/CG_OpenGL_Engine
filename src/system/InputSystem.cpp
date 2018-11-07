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
    if(input->isKeyRepeated(SDL_SCANCODE_W)) {
        increase = glm::vec3(0.0f,0.0f,1.0f);
    }
    if(input->isKeyRepeated(SDL_SCANCODE_A)){
        increase = glm::vec3(-1.0f,0.0f,0.0f);
    }
    if(input->isKeyRepeated(SDL_SCANCODE_S)){
        increase = glm::vec3(0.0f,0.0f,-1.0f);
    }
    if(input->isKeyRepeated(SDL_SCANCODE_D)){
        increase = glm::vec3(1.0f,0.0f,0.0f);
    }
    if(input->isKeyRepeated(SDL_SCANCODE_Q)){
        increase = glm::vec3(0.0f,-1.0f,0.0f);
    }
    if(input->isKeyRepeated(SDL_SCANCODE_E)){
        increase = glm::vec3(0.0f,1.0f,0.0f);
    }

    scene->getCamera().velocity.velocity = increase;
    scene->getCamera().view.position += increase;
    // scene->getCamera().target += increase;
}
