#include "PhysicsSystem.h"

#include <glm/vec3.hpp>

#include "Components.h"
#include "../engine/Scene.h"

PhysicsSystem::PhysicsSystem() {};

PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::init() {

}

void PhysicsSystem::update(const float &tps, Scene* scene) {
    applyRotation(tps, scene);
    applyMovement(tps, scene);

}

void PhysicsSystem::cleanup() {

}

void PhysicsSystem::applyRotation(const float &tps, Scene* scene) {
    applyEntityRotation(tps, scene);
    applyCameraRotation(tps, scene);
}

void PhysicsSystem::applyEntityRotation(const float &tps, Scene *scene) {
    for (auto e : scene->getEntities().withComponents<Transform, Action, Motion>()) {
        Transform* t = e.getComponent<Transform>();
        Action* a = e.getComponent<Action>();
        Motion* m = e.getComponent<Motion>();

        t->lastRotation = t->rotation;
    }
}

void PhysicsSystem::applyCameraRotation(const float &tps, Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Camera, Mouse, Motion>()) {
        Camera* c = e.getComponent<Camera>();
        Mouse* m = e.getComponent<Mouse>();
        Motion* mov = e.getComponent<Motion>();

        c->yaw -= m->dx * mov->rotSpeed * tps;
        c->pitch -= m->dy * mov->rotSpeed * tps;
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

void PhysicsSystem::applyMovement(const float &tps, Scene *scene) {
    applyEntityMovement(tps, scene);
    applyCameraMovement(tps, scene);
}

void PhysicsSystem::applyEntityMovement(const float &tps, Scene *scene) {
    for(auto e : scene->getEntities().withComponents<Transform, Action, Motion>()) {
        Transform* t = e.getComponent<Transform>();
        Action* a = e.getComponent<Action>();
        Motion* m = e.getComponent<Motion>();

        t->lastPosition = t->position;
        t->lastScale = t->scale;
    }
}

void PhysicsSystem::applyCameraMovement(const float &tps, Scene* scene) {
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
            m->direction = glm::normalize(x + y + z) * m->movSpeed * tps;
            c->position += m->direction;
        }
    }
}
