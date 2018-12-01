#ifndef SCENE_H_
#define SCENE_H_

#include "Components.h"
#include "../util/Serializable.h"
#include "../factory/EntityFactory.h"
#include "../environment/DirectionalLight.h"
#include "../environment/Fog.h"
#include "../environment/Skybox.h"
#include "../environment/Terrain.h"

class Scene : public Serializable{

public:

    Scene();

    ~Scene();

    EntityFactory& getEntities();

    DirectionalLight& getDirectional();

    Fog& getFog();

    Terrain& getTerrain();

    Skybox& getSky();

    virtual void serialize(std::ofstream &out) override;

    virtual bool deserialize(std::ifstream &stream) override;

private:

    EntityFactory ef;
    DirectionalLight light;
    Fog fog;
    Terrain terrain;
    Skybox sky;

};

#endif
