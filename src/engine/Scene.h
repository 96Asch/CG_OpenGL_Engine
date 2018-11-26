#ifndef SCENE_H_
#define SCENE_H_

#include "Components.h"
#include "../factory/EntityFactory.h"
#include "../util/Serializable.h"

class Entity;

class Scene : public Serializable{

public:

    Scene();

    ~Scene();

    EntityFactory& getEntities();

    virtual void serialize(std::ofstream &out) override;

    virtual bool deserialize(std::ifstream &stream) override;

private:

    EntityFactory ef;

};

#endif
