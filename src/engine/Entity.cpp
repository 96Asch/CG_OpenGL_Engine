#include "Entity.h"
#include <iostream>

Entity::Entity() : id(0), factory(nullptr) {}

Entity::Entity(const uint32_t &id, EntityFactory* factory)
                : id(id), factory(factory) {}

bool Entity::hasComponent(const ComponentMask &mask) {
    return (componentMask & mask) == mask;
}

bool Entity::isEntity(const uint64_t &id) {
    return this->id == id;
}

std::ostream& operator<<(std::ostream &stream, const Entity &entity) {
    stream << "Entity: { id : "<< entity.id << " } { mask : "
                  << entity.componentMask << " }" << std::endl;
    return stream;
}
