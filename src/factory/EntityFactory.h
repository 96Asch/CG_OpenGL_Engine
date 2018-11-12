#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include <deque>
#include <vector>
#include <unordered_set>
#include "../engine/Engine.h"
#include "ComponentFactory.h"

class Entity;

class EntityFactory {

public:

    EntityFactory();

    ~EntityFactory();

    Entity createEntity();

    void removeEntity(const uint64_t &id);

    void addComponent(Component* component);

private:
    friend class Entity;

    uint64_t freeId;
    std::vector<Entity> entities;
    ComponentFactory compFactory;
};

#endif
