#ifndef ENTITY_H_
#define ENTITY_H_

#include <unordered_set>
#include "../component/Component.h"

class EntityFactory;

class Entity {

public:
    Entity(const uint32_t &id, EntityFactory* factory);
    ~Entity();

    template <typename T>
    T* getComponent();

    bool hasComponent();

private:
    friend class EntityFactory;

    uint64_t id;
    uint64_t componentMask;
    EntityFactory* factory;

};

template <typename T>
T* Entity::getComponent() {

}

#endif
