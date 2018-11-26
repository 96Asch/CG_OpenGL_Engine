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
    
    template <typename T>
    T* getComponent();

};

#include "../factory/EntityFactory.h"

template <typename T>
T* Entity::getComponent() {
    return ef->getComponent<T>(id);
}

inline std::ostream& operator<<(std::ostream &stream, const Entity &e) {
    stream << "Entity: { id : " << e.id << " }";
    if(e.ef)
        stream << ", { mask : " << e.ef->getMask(e.id) << " }";
    return stream;
}


#endif
