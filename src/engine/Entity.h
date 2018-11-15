#ifndef ENTITY_H_
#define ENTITY_H_

#include <bitset>
#include "Global.h"

class EntityFactory;

typedef std::bitset<Global::NUM_BITS> ComponentMask;

class Entity {

public:

    Entity();

    ~Entity() = default;

    template <typename... T>
    bool hasComponent() const;

    bool hasComponent(const ComponentMask &mask);

    template <typename T>
    T* getComponent();

    bool isEntity(const uint64_t &id);

    friend std::ostream& operator<<(std::ostream &stream, const Entity &entity);

private:
    friend class EntityFactory;

    Entity(const uint32_t &id, EntityFactory* factory);

    uint64_t id;
    ComponentMask componentMask;
    EntityFactory* factory;
};

#include "../factory/EntityFactory.h"

template <typename... T>
bool Entity::hasComponent() const {
    return factory->hasComponent<T...>(*this);
};

template <typename T>
T* Entity::getComponent() {
    T* component = factory->getComponent<T>(*this);
    assert(component != nullptr);
    return component;
}

#endif
