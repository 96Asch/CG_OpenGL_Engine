#include "PhysicsSystem.h"

#include <glm/vec3.hpp>

#include "Components.h"
#include "../engine/Scene.h"

PhysicsSystem::PhysicsSystem() {};

PhysicsSystem::~PhysicsSystem() {};

void PhysicsSystem::init() {

}

void PhysicsSystem::updateStep(const float &tps, Scene* scene) {
    applyRotation(tps, scene);
    applyMovement(tps, scene);

}

void PhysicsSystem::cleanup() {

}

void PhysicsSystem::applyRotation(const float &tps, Scene* scene) {
    applyCameraRotation(tps, scene);
}

void PhysicsSystem::applyCameraRotation(const float &tps, Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Camera, Rotation, Mouse, Motion>()) {
        Camera* c = e.getComponent<Camera>();
        Mouse* m = e.getComponent<Mouse>();
        Motion* mov = e.getComponent<Motion>();
        Rotation* r = e.getComponent<Rotation>();

        r->lastRotation = r->rotation;
        r->rotation.y -= m->dx * mov->rotSpeed * tps;
        r->rotation.x -= m->dy * mov->rotSpeed * tps;
        c->lastTarget = c->target;
        c->lastUp = c->up;

        if(r->rotation.x > 89.0f)
            r->rotation.x = 89.0f;
        if(r->rotation.x < -89.0f)
            r->rotation.x = -89.0f;

        glm::vec3 target;
        target.x = -cos(glm::radians(r->rotation.x)) * sin(glm::radians(r->rotation.y));
        target.y = -sin(glm::radians(r->rotation.x));
        target.z = -cos(glm::radians(r->rotation.y)) * cos(glm::radians(r->rotation.x));
        c->target = glm::normalize(target);
        c->right = glm::normalize(glm::cross(c->target, scene->getUpDirection()));
        c->up = glm::normalize(glm::cross(c->right, c->target));
    }
}

void PhysicsSystem::applyMovement(const float &tps, Scene *scene) {
    applyCameraMovement(tps, scene);
}

void PhysicsSystem::applyCameraMovement(const float &tps, Scene* scene) {
    for(auto e : scene->getEntities().withComponents<Camera, Position, Action, Motion>()) {
        Action* a = e.getComponent<Action>();
        Camera* c = e.getComponent<Camera>();
        Motion* m = e.getComponent<Motion>();
        Position* p = e.getComponent<Position>();

        glm::vec3 x(0.0f), y(0.0f), z(0.0f);
        m->direction = glm::vec3(0.0f);
        p->lastPosition = p->position;
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
            p->position += m->direction;
        }
    }
}
