#include "PhysicsSystem.h"

#include <glm/vec3.hpp>

#include "Components.h"
#include "../engine/Scene.h"

PhysicsSystem::PhysicsSystem() {};

PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::init() {

}

void PhysicsSystem::update(Scene* scene) {
    scene->getCamera().velocity.velocity = glm::vec3(0.0f);
    applyMovement(&scene->getCamera().input, &scene->getCamera().view, &scene->getCamera().velocity);
}

void PhysicsSystem::cleanup() {

}

void PhysicsSystem::applyMovement(InputComponent *input, ViewComponent* view, VelocityComponent* velocity) {
    if(input->action != 0) {
        if(input->action & (Action::MOVE_FORWARD | Action::MOVE_BACKWARD)) {
            velocity->velocity = view->target * velocity->speed;
            if(input->action & Action::MOVE_BACKWARD)
                velocity->velocity *= -1;
            // else
                // view->position -= velocity->velocity;
        }
        if(input->action & (Action::MOVE_LEFT | Action::MOVE_RIGHT)) {
            velocity->velocity = glm::normalize(glm::cross(view->target, view->up))
                                 * velocity->speed;
            if(input->action & Action::MOVE_LEFT)
                velocity->velocity *= -1;
            // else
                // view->position += velocity->velocity;
        }
        if(input->action & (Action::MOVE_UP | Action::MOVE_DOWN)) {
            velocity->velocity = view->up * velocity->speed;
            if(input->action & Action::MOVE_DOWN)
                velocity->velocity *= -1;
            // else
                // view->position -= velocity->velocity;
        }
        view->position += velocity->velocity;
    }
}
