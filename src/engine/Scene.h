#ifndef SCENE_H_
#define SCENE_H_

#include "Components.h"
#include "Camera.h"
#include "../factory/EntityFactory.h"

class ComponentManager;
class EntityFactory;
class Entity;

class Scene {

public:

    Scene();

    ~Scene();

    Entity getEntity(const uint64_t &id);

    EntityFactory& getEntities();

    Camera& getCamera();

private:

    Camera camera;
    EntityFactory ef;

};

#endif
