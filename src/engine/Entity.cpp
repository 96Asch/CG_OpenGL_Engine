#include "Entity.h"
#include "../factory/EntityFactory.h"

Entity::Entity() : id(0), factory(nullptr) {}

Entity::Entity(const uint32_t &id, EntityFactory* factory)
                : id(id), factory(factory) {}


Entity::~Entity() {}

bool Entity::hasComponent(const ComponentMask &mask) {
    return (componentMask & mask);
}

bool Entity::isEntity(const uint64_t &id) {
    return this->id == id;
}
