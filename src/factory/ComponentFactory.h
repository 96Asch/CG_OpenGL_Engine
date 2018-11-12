#ifndef COMPONENTFACTORY_H_
#define COMPONENTFACTORY_H_

#include <typeinfo>
#include <typeindex>
#include "../datastructure/PolyMap.h"
#include "../component/Component.h"
#include "../engine/Entity.h"

class ComponentFactory {

public:

    template <class T, typename... Args>
    T& create(Entity &entity, Args... args);

private:
    friend struct Component;

    PolyMap<Component> components;

};

template <class T, typename... Args>
T& create(Entity &entity, Args... args) {
    
};


#endif
