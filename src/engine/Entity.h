#ifndef ENTITY_H_
#define ENTITY_H_

#include "../component/Component.h"

class EntityFactory;
class ComponentFactory;

class Entity {

public:
    Entity(const uint32_t &id, EntityFactory* factory);
    ~Entity();

    template <typename T>
    inline T* getComponent();

    bool hasComponent(const ComponentMask &mask);

private:
    friend class EntityFactory;
    friend class ComponentFactory;

    uint64_t id;
    uint64_t componentMask;
    EntityFactory* factory;

};

#include "../factory/EntityFactory.h"

template <class T>
T* Entity::getComponent() {
    return factory->getComponent<T>(this);
}

#endif
