#ifndef SCENE_H_
#define SCENE_H_

#include <glm/vec3.hpp>

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

    Terrain& getTerrain();

    Skybox& getSky();

    glm::vec3 getUpDirection();

    glm::vec3 getAmbient();

    float getExposure();

    virtual void serialize(std::ofstream &out) override;

    virtual bool deserialize(std::ifstream &stream) override;

private:

    EntityFactory ef;

    glm::vec3 upDirection;
    glm::vec3 ambientLight;
    float exposure;

    DirectionalLight light;
    Fog fog;
    Terrain terrain;
    Skybox sky;

};

#endif
