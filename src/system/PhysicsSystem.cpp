#include "PhysicsSystem.h"

#include <glm/vec3.hpp>

#include "Components.h"
#include "../engine/Scene.h"

PhysicsSystem::PhysicsSystem() {};

PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::init() {

}

void PhysicsSystem::update(Scene* scene) {
    applyRotation(scene);
    applyMovement(scene);

}

void PhysicsSystem::cleanup() {

}

void PhysicsSystem::applyRotation(Scene* scene) {
    applyEntityRotation(scene);
    applyCameraRotation(scene);
}

void PhysicsSystem::applyEntityRotation(Scene *scene) {
    for (auto e : scene->getEntities().withComponents<Transform, Action, Motion>()) {
        Transform* t = e.getComponent<Transform>();
        Action* a = e.getComponent<Action>();
        Motion* m = e.getComponent<Motion>();

        t->lastRotation = t->rotation;
    }
}

void PhysicsSystem::applyCameraRotation(Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Camera, Mouse, Motion>()) {
        Camera* c = e.getComponent<Camera>();
        Mouse* m = e.getComponent<Mouse>();
        Motion* mov = e.getComponent<Motion>();

        c->yaw -= m->dx * mov->rotSpeed;
        c->pitch += m->dy * mov->rotSpeed;
        c->lastTarget = c->target;
        c->lastUp = c->up;

        if(c->pitch > 89.0f)
            c->pitch = 89.0f;
        if(c->pitch < -89.0f)
            c->pitch = -89.0f;

        glm::vec3 target;
        target.x = -cos(glm::radians(c->pitch)) * sin(glm::radians(c->yaw));
        target.y = -sin(glm::radians(c->pitch));
        target.z = -cos(glm::radians(c->yaw)) * cos(glm::radians(c->pitch));
        c->target = glm::normalize(target);
        c->right = glm::normalize(glm::cross(c->target, c->worldUp));
        c->up = glm::normalize(glm::cross(c->right, c->target));
    }
}

void PhysicsSystem::applyMovement(Scene *scene) {
    applyEntityMovement(scene);
    applyCameraMovement(scene);
}

void PhysicsSystem::applyEntityMovement(Scene *scene) {
    for(auto e : scene->getEntities().withComponents<Transform, Action, Motion>()) {
        Transform* t = e.getComponent<Transform>();
        Action* a = e.getComponent<Action>();
        Motion* m = e.getComponent<Motion>();

        t->lastPosition = t->position;
        t->lastScale = t->scale;
    }
}

void PhysicsSystem::applyCameraMovement(Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Camera, Action, Motion>()) {
        Action* a = e.getComponent<Action>();
        Camera* c = e.getComponent<Camera>();
        Motion* m = e.getComponent<Motion>();

        glm::vec3 x(0.0f), y(0.0f), z(0.0f);
        m->direction = glm::vec3(0.0f);
        c->lastPosition = c->position;
        if(a->action.any()) {
            if(a->action.test(ActType::MOVE_LEFT)
                || a->action.test(ActType::MOVE_RIGHT)) {
                x = c->right;
                if(a->action.test(ActType::MOVE_LEFT))
                    x = -x;
            }
            if(a->action.test(ActType::MOVE_UP)
                || a->action.test(ActType::MOVE_DOWN)) {
                y = c->up;
                if(a->action.test(ActType::MOVE_DOWN))
                    y = -y;
            }
            if(a->action.test(ActType::MOVE_FORWARD)
            || a->action.test(ActType::MOVE_BACKWARD)) {
                z = c->target;
                if(a->action.test(ActType::MOVE_BACKWARD))
                    z = -z;
            }
            m->direction = glm::normalize(x + y + z) * m->movSpeed;
            c->position += m->direction;
            printf("right(%f,%f,%f)\n", c->position.x, c->position.y, c->position.z);
        }
    }
}
