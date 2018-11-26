#include "InputSystem.h"

#include <iostream>

#include "Components.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../input/InputHandler.h"


InputSystem::InputSystem() : System() {}

InputSystem::~InputSystem() {}


void InputSystem::init() {
    inputHandler = owner->getInputHandler();
}

void InputSystem::update(Scene* scene) {
    handleMouse(scene);
    handleKeys(scene);
}

void InputSystem::cleanup() {
    inputHandler = nullptr;
}

void InputSystem::handleMouse(Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Mouse>()) {
        Mouse* m = e.getComponent<Mouse>();
        m->dx = m->dy = 0.0f;
        if(inputHandler->isMouseHeld(SDL_BUTTON_LEFT)) {
            inputHandler->getDelta(m->dx, m->dy);
        }
        inputHandler->getMousePosition(m->x, m->y);
    }
}

void InputSystem::handleKeys(Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Action>()) {
        Action* a = e.getComponent<Action>();
        a->action.reset();
        if(inputHandler->isKeyRepeated(SDLK_w)) {
            a->addAction(ActType::MOVE_FORWARD);
        }
        if(inputHandler->isKeyRepeated(SDLK_a)){
            a->addAction(ActType::MOVE_LEFT);
        }
        if(inputHandler->isKeyRepeated(SDLK_s)){
            a->addAction(ActType::MOVE_BACKWARD);
        }
        if(inputHandler->isKeyRepeated(SDLK_d)){
            a->addAction(ActType::MOVE_RIGHT);
        }
        if(inputHandler->isKeyRepeated(SDLK_q)){
            a->addAction(ActType::MOVE_UP);
        }
        if(inputHandler->isKeyRepeated(SDLK_e)){
            a->addAction(ActType::MOVE_DOWN);
        }
    }
}
