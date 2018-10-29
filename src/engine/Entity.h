#ifndef ENTITY_H_
#define ENTITY_H_

#include <unordered_set>
#include "../component/Component.h"

class Entity {

public:
    Entity();
    ~Entity();

    template <typename T>
    T* getComponent(const CompType &type);

    bool hasComponent(const CompType &type);

private:
    
    std::unordered_set<Component*> components;

};

template <typename T>
T* Entity::getComponent(const CompType &type) {
    s
}

#endif
