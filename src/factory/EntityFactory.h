#ifndef ENTITYFACTORY_H_
#define ENTITYFACTORY_H_

#include <stack>
#include <vector>
#include <cstdint>
#include <string>
#include <bitset>
#include <map>

#include "../datastructure/PolyMap.h"
#include "../component/Component.h"
#include "Global.h"


typedef std::bitset<Global::NUM_BITS> ComponentMask;

class Entity;

class EntityFactory {

public:

    template <class Derived>
    class BaseIterator {

    public:

        typedef Derived self_type;
        typedef Entity value_type;
        typedef Entity& reference;
        typedef Entity* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;

        self_type& operator++() {
            next();
            return *static_cast<Derived*>(this);
        };

        reference operator*() {
            return ef->getEntity(index);
        };

        bool operator==(const self_type& rhs) {
            return index == rhs.index;
        };

        bool operator!=(const self_type& rhs) {
            return index != rhs.index;
        };

    protected:

        BaseIterator(EntityFactory* ef, const ComponentMask &mask, const size_t &index)
        : ef(ef), mask(mask), index(index) {};

        void next();

        bool condition();


        EntityFactory* ef;
        ComponentMask mask;
        size_t index;
    };

    class EntityGroup {

    public:

        class MaskIterator : public BaseIterator<MaskIterator> {

        public:
            MaskIterator(EntityFactory* ef,
                         const ComponentMask &mask,
                         const size_t &index)
                : BaseIterator(ef, mask, index) {
                BaseIterator<MaskIterator>::next();
            }

        private:

        };

        MaskIterator begin() { return MaskIterator(ef, mask, 0); };

        MaskIterator end() { return MaskIterator(ef, mask, ef->numEntities()); };

        const MaskIterator begin() const { return MaskIterator(ef, mask, 0); };

        const MaskIterator end() const { return MaskIterator(ef, mask, ef->numEntities()); };

    private:
        friend class EntityFactory;

        EntityGroup(EntityFactory* ef, const ComponentMask &mask) : ef(ef), mask(mask) {};

        EntityFactory* ef;
        ComponentMask mask;

    };

    EntityFactory();

    ~EntityFactory();

    Entity& createEntity(const std::string &test);

    void removeEntity(Entity &entity);

    Entity& getEntity(const size_t &index);

    size_t numEntities();

    template <class T>
    void addComponent(Entity &entity, T &&component);

    template <class T>
    void removeComponent(Entity &entity);

    template <class T>
    MonoListDerived<T, Component>& getComponents();

    template <class T, typename... Ts>
    EntityGroup withComponents();

    template <typename... T>
    bool hasComponent(const Entity &entity);

    template <class T>
    T* getComponent(const Entity &entity);

private:

    uint64_t freeId;
    std::stack<uint64_t> removedIds;
    std::vector<Entity> entities;
    PolyMap<Component> components;

    uint64_t generateId();

    template <class T>
    ComponentMask componentMask();

    template <class T1, class T2, class... Ts>
    ComponentMask componentMask();
};

#include "../engine/Entity.h"

template <class Derived>
void EntityFactory::BaseIterator<Derived>::next() {
    ++index;
    while(index < ef->numEntities() && !condition())
        ++index;
}

template <class Derived>
bool EntityFactory::BaseIterator<Derived>::condition() {
    return ef->getEntity(index).hasComponent(mask);
}


template <class T>
void EntityFactory::addComponent(Entity &entity, T &&component) {
    entity.componentMask |= componentMask<T>();
    component.owner = entity.id;
    components.insert(component);
};

template <class T>
void EntityFactory::removeComponent(Entity &entity) {
    uint64_t id = entity.id;
    Component removed;
    entity.componentMask &= ~(1UL << componentMask<T>());
}

template <class T>
MonoListDerived<T, Component>& EntityFactory::getComponents() {
    return components.getList<T>();
}

template <class T, typename... Ts>
EntityFactory::EntityGroup EntityFactory::withComponents() {
    auto mask = componentMask<T, Ts...>();
    return EntityGroup(this, mask);
}

template <typename... T>
bool EntityFactory::hasComponent(const Entity &entity) {
    auto mask = componentMask<T...>();
    return (entity.componentMask & mask) == mask;
}

template <class T>
T* EntityFactory::getComponent(const Entity &entity) {
    for(auto &c : components.getList<T>())
        if(c.owner == entity.id)
            return &c;
    return nullptr;
}

template <class T>
ComponentMask EntityFactory::componentMask() {
    ComponentMask mask;
    mask.set(T::bit());
    return mask;
}

template <class T1, class T2, class... Ts>
ComponentMask EntityFactory::componentMask() {
    return componentMask<T1>() | componentMask<T2, Ts...>();
}

#endif
