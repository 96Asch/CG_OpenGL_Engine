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

    virtual void updateStep(const float &tps, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void updateSky(const float &tps, Skybox &box);

    void updateDirectionalLight(const float &tps,
                                DirectionalLight &light,
                                const float &angle);

    void updateExplosions(const float &tps, std::shared_ptr<Scene> scene);

    void updateDestruct(const float &tps, std::shared_ptr<Scene> scene);

};

#endif
