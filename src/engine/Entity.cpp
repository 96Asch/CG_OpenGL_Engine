#include "Entity.h"
#include "../factory/EntityFactory.h"


Entity::Entity(const uint32_t &id, EntityFactory* factory)
                : id(id), factory(factory) {};


Entity::~Entity() {

}
