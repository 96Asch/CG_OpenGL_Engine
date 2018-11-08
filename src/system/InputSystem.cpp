#include "InputSystem.h"

#include <iostream>

#include "Components.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"
#include "../input/InputHandler.h"


InputSystem::InputSystem() : System() {}

InputSystem::~InputSystem() {}


void InputSystem::init() {
    inputHandler = owner->getInputHandler();
}

void InputSystem::update(Scene* scene) {
    scene->getCamera().input.action = 0;
    handleKeys(&scene->getCamera().input);
}

void InputSystem::cleanup() {
    inputHandler = nullptr;
}

void InputSystem::handleKeys(InputComponent* input) {
    if(inputHandler->isKeyRepeated(SDLK_w)) {
        input->addAction(Action::MOVE_FORWARD);
    }
    if(inputHandler->isKeyRepeated(SDLK_a)){
        input->addAction(Action::MOVE_LEFT);
    }
    if(inputHandler->isKeyRepeated(SDLK_s)){
        input->addAction(Action::MOVE_BACKWARD);
    }
    if(inputHandler->isKeyRepeated(SDLK_d)){
        input->addAction(Action::MOVE_RIGHT);
    }
    if(inputHandler->isKeyRepeated(SDLK_q)){
        input->addAction(Action::MOVE_UP);
    }
    if(inputHandler->isKeyRepeated(SDLK_e)){
        input->addAction(Action::MOVE_DOWN);
    }

    std::cout << input->action << std::endl;
}
