#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "../datastructure/PolyMap.h"
#include <iostream>

class Entity;
struct Component;

class ComponentManager {

public:

    ComponentManager() {};

    ~ComponentManager() {};

    template <class T>
    void create(Entity &entity, T &&component);

    template <class T>
    void remove(Entity &entity);

    template <class T>
    MonoListDerived<T, Component>& getComponents();

private:

    PolyMap<Component> components;

};

#include "../engine/Entity.h"
#include "../component/Component.h"

template <class T>
void ComponentManager::create(Entity &entity, T &&component) {
    entity.componentMask |= component.mask;
    component.owner = entity.id;
    components.insert(component);
};

template <class T>
void ComponentManager::remove(Entity &entity) {
    uint64_t id = entity.id;
    Component removed;
    components.remove_if([id](const T &comp){
        return comp.owner == id;
    }, removed);
    entity.componentMask &= ~(1UL << removed.mask);
}

template <class T>
MonoListDerived<T, Component>& ComponentManager::getComponents() {
    return components.getList<T>();
}

#endif
