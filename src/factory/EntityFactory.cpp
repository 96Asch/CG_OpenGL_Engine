#include <sstream>
#include <string>

#include "EntityFactory.h"
#include "Components.h"

EntityFactory::EntityFactory() : index(0) {
    	masks.clear();
}

EntityFactory::~EntityFactory() {}

bool EntityFactory::valid(const EntityId &id){
		return id.index < entityVersion.size()
            && entityVersion[id.index] == id.version;
}


Entity EntityFactory::get(const EntityId &id){
	return Entity(id, this);
}

ComponentMask EntityFactory::getMask(const EntityId &id) {
    if(valid(id))
        return masks[id.index];
    return ComponentMask();
}

void EntityFactory::serialize(std::ofstream &) {}

bool EntityFactory::deserialize(std::ifstream &stream) {
    bool firstAcc(false), lastAcc(false);
    Entity newEnt = createEntity();
    do {
        std::string comp;
        stream >> std::ws;
        if (std::getline(stream, comp)) {
            if(!firstAcc && comp == "{")
                firstAcc = true;
            else if (firstAcc && comp == "}")
                lastAcc = true;
            else if(comp == "[model]")
                addComponent(newEnt.id, Model(stream));
            else if (comp == "[action]")
                addComponent(newEnt.id, Action(stream));
            else if (comp == "[camera]")
                addComponent(newEnt.id, Camera(stream));
            else if (comp == "[material]")
                addComponent(newEnt.id, Material(stream));
            else if (comp == "[mouse]")
                addComponent(newEnt.id, Mouse(stream));
            else if (comp == "[transform]")
                addComponent(newEnt.id, Transform(stream));
            else if (comp == "[motion]")
                addComponent(newEnt.id, Motion(stream));
            else if (comp == "[pointlight]")
                addComponent(newEnt.id, PointLight(stream));
            else if (comp == "[spotlight]")
                addComponent(newEnt.id, SpotLight(stream));
            else if (comp.front() == '[' && comp.back() == ']') {
                std::cerr << "Warning: Unidentified component: " << comp << std::endl;
            }
        }
        else return false;
    } while(stream && firstAcc && !lastAcc);
    return true;
}


Entity EntityFactory::createEntity(){
	uint32_t newIndex, newVersion;
	if (freeList.empty()) {
		newIndex = index++;
		AccomodateEntity(newIndex);
		newVersion = entityVersion[newIndex] = 1;
	}
	else {
		newIndex = freeList.front();
		freeList.pop_front();
		newVersion = entityVersion[newIndex];
	}
	return Entity({newIndex, newVersion}, this);
}

size_t EntityFactory::capacity(){
	return masks.size();
}

size_t EntityFactory::numEntities(){
	return masks.size() - freeList.size();
}

void EntityFactory::destroyEntity(const EntityId &id) {
	const uint32_t index = id.index;
	for (size_t i = 0; i < components.size(); i++){
		BlockAllocator* pool = components[i];
		if (pool && masks[index].test(i))
			pool->destroy(index);
	}
	masks[index].reset();
	entityVersion[index]++;
	freeList.push_back(index);
}
