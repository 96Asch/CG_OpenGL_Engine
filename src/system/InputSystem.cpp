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
    handleMouse(&scene->getCamera().mouse);
    handleKeys(&scene->getCamera().action);
}

void InputSystem::cleanup() {
    inputHandler = nullptr;
}

void InputSystem::handleMouse(MouseComponent* mouse) {
    mouse->dx = mouse->dy = 0.0f;
    if(inputHandler->isMouseHeld(SDL_BUTTON_LEFT)) {
        inputHandler->getDelta(mouse->dx, mouse->dy);
    }
    inputHandler->getMousePosition(mouse->x, mouse->y);
}

void InputSystem::handleKeys(ActionComponent* action) {
    action->action = 0;
    if(inputHandler->isKeyRepeated(SDLK_w)) {
        action->addAction(Action::MOVE_FORWARD);
    }
    if(inputHandler->isKeyRepeated(SDLK_a)){
        action->addAction(Action::MOVE_LEFT);
    }
    if(inputHandler->isKeyRepeated(SDLK_s)){
        action->addAction(Action::MOVE_BACKWARD);
    }
    if(inputHandler->isKeyRepeated(SDLK_d)){
        action->addAction(Action::MOVE_RIGHT);
    }
    if(inputHandler->isKeyRepeated(SDLK_q)){
        action->addAction(Action::MOVE_UP);
    }
    if(inputHandler->isKeyRepeated(SDLK_e)){
        action->addAction(Action::MOVE_DOWN);
    }
}
