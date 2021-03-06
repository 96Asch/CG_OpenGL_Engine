#ifndef PHYSICSSYSTEM_H_
#define PHYSICSSYSTEM_H_

#include "System.h"

class Scene;
class Camera;

struct ActionComponent;
struct ViewComponent;
struct VelocityComponent;

class PhysicsSystem : public System {

public:

    PhysicsSystem();

    virtual ~PhysicsSystem() override;

    virtual void init() override;

    virtual void updateStep(const float &tps, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void applyRotation(const float &tps, std::shared_ptr<Scene> scene);

    void applyCameraRotation(const float &tps, std::shared_ptr<Scene> scene);

    void applyMovement(const float &tps, std::shared_ptr<Scene> scene);

    void applyCameraMovement(const float &tps, std::shared_ptr<Scene> scene);

};

#endif
