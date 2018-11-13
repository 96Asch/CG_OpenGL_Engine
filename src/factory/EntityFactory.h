#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include <deque>
#include <vector>
#include <type_traits>
#include <typeindex>
#include <typeinfo>

#include "../component/Component.h"
#include "../datastructure/PolyMap.h"

class Entity;

class ComponentFactory {

public:

    ComponentFactory();

    ~ComponentFactory();

    template <class T, typename... Args,
    typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    T& create(Entity &entity, Args... args);

    template <class T,
    typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    void remove(Entity &entity);

    void clear(Entity &entity);

    template <class T,
    typename std::enable_if_t<std::is_base_of<Component, T>::value>>
    T* getComponent(const Entity &entity);

private:

    PolyMap<Component> components;

};

class EntityFactory {

public:

    EntityFactory();

    ~EntityFactory();

    Entity* createEntity();

    void removeEntity(Entity &entity);

    template <typename T>
    inline T* getComponent(const Entity &entity);

private:
    friend class Entity;

    std::vector<Entity> entities;
    ComponentFactory compFactory;
};

#include "../engine/Entity.h"

template <typename T>
inline T* EntityFactory::getComponent(const Entity &entity) {
    return compFactory.getComponent<T>(entity);
}

template <class T, typename... Args,
typename std::enable_if_t<std::is_base_of<Component, T>::value>>
T& ComponentFactory::create(Entity &entity, Args... args) {
    T component(args...);
    components.insert(component);
    entity.componentMask |= component.mask;
    return component;
};

template <class T,
typename std::enable_if_t<std::is_base_of<Component, T>::value>>
void ComponentFactory::remove(Entity &entity) {
    uint64_t id = entity.id;
    Component removed;
    components.remove_if([id](const T &comp){
        return comp.owner == id;
    }, removed);
    entity.componentMask &= ~(1UL << removed.mask);
}


template <class T,
typename std::enable_if_t<std::is_base_of<Component, T>::value>>
T* ComponentFactory::getComponent(const Entity &entity) {
    uint64_t id = entity.id;
    return components.get_if<T>([id](const T &comp){
        return comp.owner == id;
    });
}


#endif
