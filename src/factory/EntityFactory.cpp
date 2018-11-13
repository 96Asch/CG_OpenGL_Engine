#include "EntityFactory.h"
#include "Components.h"
#include "ComponentManager.h"

EntityFactory::EntityFactory(ComponentManager* cm) : freeId(1), cm(cm) {}

EntityFactory::~EntityFactory() {}

Entity& EntityFactory::createEntity(const std::string &test) {
    Entity entity(generateId(), this);
    entities.push_back(entity);
    cm->create(entity, ModelComponent(test));
    cm->create(entity, MaterialComponent("texture/grassy3.png"));
    cm->create(entity, TransformComponent());
    return entities.back();
}

void EntityFactory::removeEntity(Entity &entity) {
    uint64_t id = entity.id;
    // cm->clear(entity);
    entities.erase(std::remove_if(entities.begin(),
                                  entities.end(),
                                  [id](const auto &e){
        return (id == e.id);
    }));
}

Entity EntityFactory::getEntity(const uint64_t &id) {
    for(Entity e : entities)
        if(e.isEntity(id))
            return e;
    return Entity(0, nullptr);
}

uint64_t EntityFactory::generateId() {
    uint64_t newId;
    if(!removedIds.empty()) {
        newId = removedIds.top();
        removedIds.pop();
    }
    else {
        newId = freeId;
        ++freeId;
    }
    return newId;
}
