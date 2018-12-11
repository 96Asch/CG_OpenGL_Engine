#include "LogicSystem.h"

#include <iostream>
#include <cmath>

#include "Components.h"
#include "Global.h"
#include "../engine/Scene.h"
#include "../input/InputHandler.h"

const float EXPLOSION_SPEED = 2.0f;
const float MAX_EXPLODE_DIST = 50.0f;
const float SECONDS_BEFORE_NEXT_EXPLODE = 20.0f;

LogicSystem::LogicSystem() : System(), firstUpdate(true) {}

LogicSystem::~LogicSystem() {}


void LogicSystem::init() {}

void LogicSystem::updateStep(const float &tps, std::shared_ptr<Scene> scene) {
    if(!firstUpdate)
        checkIntersections(scene);
    else
        firstUpdate = false;
    explodeAll(tps, scene);
}

void LogicSystem::cleanup() {
}

void LogicSystem::checkIntersections(std::shared_ptr<Scene> scene) {
    for(auto e1 : scene->getEntities().withComponents<Interact>()) {
        Position* p1 = e1.getComponent<Position>();
        Interact* i1 = e1.getComponent<Interact>();
        for(auto e2 : scene->getEntities().withComponents<Interact, Position>()) {
            Position* p2 = e2.getComponent<Position>();
            Interact* i2 = e2.getComponent<Interact>();
            if(e1 != e2) {
                if(std::abs(p1->interpolated.x - p2->interpolated.x) < i1->halfExtents.x + i2->halfExtents.x) {
                      if(std::abs(p1->interpolated.y - p2->interpolated.y) < i1->halfExtents.y + i2->halfExtents.y) {
                          if(std::abs(p1->interpolated.z - p2->interpolated.z) < i1->halfExtents.z + i2->halfExtents.z) {
                              if(!e2.hasComponent<Camera>() && !e2.hasComponent<Explode>()) {
                                  e2.addComponent<Explode>(true, EXPLOSION_SPEED, MAX_EXPLODE_DIST);
                              }
                          }
                      }
                   }
            }
        }

    }
}

void LogicSystem::explodeAll(const float &tps, std::shared_ptr<Scene> scene) {
    secondsCounter += tps;
    for(auto e1 : scene->getEntities().withComponents<Explode>()) {
        if(secondsCounter > SECONDS_BEFORE_NEXT_EXPLODE) {
            secondsCounter = 0.0f;
            for(auto e2 : scene->getEntities().withComponents<Model>()) {
                if(e1 != e2 && !e2.hasComponent<Explode>()) {
                    e2.addComponent<Explode>(true, EXPLOSION_SPEED, MAX_EXPLODE_DIST);
                }
            }
        }
    }
}
