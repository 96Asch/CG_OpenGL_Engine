#ifndef ENVIRONMENTSYSTEM_H_
#define ENVIRONMENTSYSTEM_H_

#include "System.h"

struct DirectionalLight;
struct Skybox;

class EnvironmentSystem : public System {

public:

    EnvironmentSystem();

    virtual ~EnvironmentSystem() override;

    virtual void init() override;

    virtual void update(Scene* scene) override;

    virtual void cleanup() override;

private:

    void updateSky(Skybox &box);

    void updateDirectionalLight(DirectionalLight &light, const float &angle);

};

#endif
