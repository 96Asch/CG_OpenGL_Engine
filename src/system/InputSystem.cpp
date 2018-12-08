#include "InputSystem.h"

#include <iostream>

#include "Components.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../input/InputHandler.h"


InputSystem::InputSystem() : System() {}

InputSystem::~InputSystem() {}


void InputSystem::init() {}

void InputSystem::updateStep(const float &, std::shared_ptr<Scene> scene) {
    handleMouse(scene);
    handleKeys(scene);
}

void InputSystem::cleanup() {
}

    void InputSystem::handleMouse(std::shared_ptr<Scene> scene) {
    for(auto e : scene->getEntities().withComponents<Mouse>()) {
        Mouse* m = e.getComponent<Mouse>();
        m->dx = m->dy = 0.0f;
        if(Input::INPUT->isMouseHeld(GLFW_MOUSE_BUTTON_LEFT)) {
            Input::INPUT->getDelta(m->dx, m->dy);
        }
        Input::INPUT->getMousePosition(m->x, m->y);
    }
}

void InputSystem::handleKeys(std::shared_ptr<Scene> scene) {
    for(auto e : scene->getEntities().withComponents<Action>()) {
        Action* a = e.getComponent<Action>();
        a->action.reset();
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_W)) {
            a->addAction(ActType::MOVE_FORWARD);
        }
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_A)){
            a->addAction(ActType::MOVE_LEFT);
        }
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_S)){
            a->addAction(ActType::MOVE_BACKWARD);
        }
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_D)){
            a->addAction(ActType::MOVE_RIGHT);
        }
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_Q)){
            a->addAction(ActType::MOVE_UP);
        }
        if(Input::INPUT->isKeyRepeated(GLFW_KEY_E)){
            a->addAction(ActType::MOVE_DOWN);
        }
    }
}
