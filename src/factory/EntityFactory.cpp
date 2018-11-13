#include "EntityFactory.h"

EntityFactory::EntityFactory() {}

EntityFactory::~EntityFactory() {}

Entity* EntityFactory::createEntity() {

    return nullptr;
}

void EntityFactory::removeEntity(Entity &entity) {
    uint64_t id = entity.id;
    compFactory.clear(entity);
    entities.erase(std::remove_if(entities.begin(),
                                  entities.end(),
                                  [id](const Entity &e){
        return (id == e.id);
    }));
}

ComponentFactory::ComponentFactory() {}

ComponentFactory::~ComponentFactory() {}

void ComponentFactory::clear(Entity &entity) {
    uint64_t id = entity.id;
    Component removed;
    // components.remove_if([id](const Component &comp){
    //     return comp.owner == id;
    // }, removed);
    entity.componentMask = ComponentMask::NIL;
}
