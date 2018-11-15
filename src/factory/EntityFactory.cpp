#include "EntityFactory.h"
#include "Components.h"

EntityFactory::EntityFactory() : freeId(1) {}

EntityFactory::~EntityFactory() {}

Entity& EntityFactory::createEntity(const std::string &test) {
    Entity entity(generateId(), this);
    addComponent(entity, ModelComponent(test));
    addComponent(entity, MaterialComponent("texture/grassy3.png"));
    addComponent(entity, TransformComponent());
    entities.push_back(entity);
    return entities.back();
}

void EntityFactory::removeEntity(Entity &entity) {
    uint64_t id = entity.id;
    entities.erase(std::remove_if(entities.begin(),
                                  entities.end(),
                                  [id](const auto &e){
        return (id == e.id);
    }));
}

Entity& EntityFactory::getEntity(const size_t &index) {
    if (0 < index && index < entities.size())
        return entities[index];
    return entities.front();
}

size_t EntityFactory::numEntities() {
    return entities.size();
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
