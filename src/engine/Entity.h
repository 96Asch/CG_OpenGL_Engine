#ifndef ENTITY_H_
#define ENTITY_H_

#include "../component/Component.h"

class EntityFactory;
class ComponentManager;

class Entity {

public:

    Entity();

    ~Entity();

    bool hasComponent(const ComponentMask &mask);

    bool isEntity(const uint64_t &id);

private:
    friend class EntityFactory;
    friend class ComponentManager;

    Entity(const uint32_t &id, EntityFactory* factory);

    uint64_t id;
    uint64_t componentMask;
    EntityFactory* factory;

};

#endif
