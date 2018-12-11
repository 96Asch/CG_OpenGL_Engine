#ifndef ENTITY_H_
#define ENTITY_H_

#include <iostream>
#include "EntityId.h"
#include "Global.h"

class EntityFactory;


struct Entity{

    Entity(const EntityId &id, EntityFactory* ef)
        : id(id), ef(ef) {};

    EntityId id;
    EntityFactory* ef;

    template <typename T, typename... Args>
    void addComponent(Args... args);

    template <typename T>
    T* getComponent();

    template <typename T>
    bool hasComponent();

    inline void destroy();

};

#include "../factory/EntityFactory.h"

template <typename T, typename... Args>
void Entity::addComponent(Args... args) {
    ef->addComponent(id, T(args...));
}

template <typename T>
T* Entity::getComponent() {
    return ef->getComponent<T>(id);
}

template <typename T>
bool Entity::hasComponent() {
    return ef->hasComponent<T>(id);
}

void Entity::destroy() {
    ef->destroyEntity(id);
}

inline std::ostream& operator<<(std::ostream &stream, const Entity &e) {
    stream << "Entity: { id : " << e.id << " }";
    if(e.ef)
        stream << ", { mask : " << e.ef->getMask(e.id) << " }";
    return stream;
}

inline bool operator==(const Entity &e1, const Entity &e2) {
    return e1.id == e2.id;
}

inline bool operator!=(const Entity &e1, const Entity &e2) {
    return !(e1.id == e2.id);
}



#endif
