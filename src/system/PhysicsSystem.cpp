#include "PhysicsSystem.h"

#include <glm/vec3.hpp>

#include "Components.h"
#include "../engine/Scene.h"
#include "../engine/Camera.h"

PhysicsSystem::PhysicsSystem() {};

PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::init() {

}

void PhysicsSystem::update(Scene* scene) {
    applyRotation(scene->getCamera());
    applyMovement(scene->getCamera());
}

void PhysicsSystem::cleanup() {

}

void PhysicsSystem::applyRotation(Camera &camera) {
    camera.yaw += camera.mouse.dx;
    camera.pitch -= camera.mouse.dy;
    camera.lastTarget = camera.target;
    camera.lastUp = camera.up;

    if(camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if(camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    glm::vec3 target;
    target.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    target.y = sin(glm::radians(camera.pitch));
    target.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));

    camera.target = glm::normalize(target);
    camera.right = glm::normalize(glm::cross(camera.target, camera.worldUp));
    camera.up = glm::normalize(glm::cross(camera.right, target));
}

void PhysicsSystem::applyMovement(Camera &camera) {
    glm::vec3 x(0.0f), y(0.0f), z(0.0f);
    camera.velocity.velocity = glm::vec3(0.0f);
    camera.lastPosition = camera.position;
    if(camera.action.action != 0) {
        if(camera.action.action & (Action::MOVE_FORWARD | Action::MOVE_BACKWARD)) {
            z = camera.target * camera.velocity.speed;
            if(camera.action.action & Action::MOVE_BACKWARD)
                z *= -1;
        }
        if(camera.action.action & (Action::MOVE_LEFT | Action::MOVE_RIGHT)) {
            x = camera.right * camera.velocity.speed;
            if(camera.action.action & Action::MOVE_LEFT)
                x *= -1;
        }
        if(camera.action.action & (Action::MOVE_UP | Action::MOVE_DOWN)) {
            z = camera.up * camera.velocity.speed;
            if(camera.action.action & Action::MOVE_DOWN)
                z *= -1;
        }
        camera.velocity.velocity = x + y + z;
        camera.position += camera.velocity.velocity;
    }
}
