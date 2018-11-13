#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include <stack>
#include <vector>
#include <cstdint>
#include <string>

class Entity;
class ComponentManager;

class EntityFactory {

public:

    EntityFactory(ComponentManager* cm);

    ~EntityFactory();

    Entity& createEntity(const std::string &test);

    void removeEntity(Entity &entity);

    Entity getEntity(const uint64_t &id);


private:
    friend class Entity;

    uint64_t generateId();

    uint64_t freeId;
    std::stack<uint64_t> removedIds;
    std::vector<Entity> entities;
    ComponentManager* cm;
};

#endif
