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
    glm::vec3 x(0.0f), y(0.0f), z(0.0f);
    view->lastPosition = view->position;
    printf("( %f, %f, %f )\n", view->lastPosition.x, view->lastPosition.y, view->lastPosition.z);
    if(input->action != 0) {
        if(input->action & (Action::MOVE_FORWARD | Action::MOVE_BACKWARD)) {
            z = view->target * velocity->speed;
            if(input->action & Action::MOVE_BACKWARD)
                z *= -1;
        }
        if(input->action & (Action::MOVE_LEFT | Action::MOVE_RIGHT)) {
            x = glm::normalize(glm::cross(view->target, view->up)) * velocity->speed;
            if(input->action & Action::MOVE_LEFT)
                x *= -1;
        }
        if(input->action & (Action::MOVE_UP | Action::MOVE_DOWN)) {
            z = view->up * velocity->speed;
            if(input->action & Action::MOVE_DOWN)
                z *= -1;
        }
        velocity->velocity = x + y + z;
        view->position += velocity->velocity;
    }
}
