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

    virtual void update(Scene* scene) override;

    virtual void cleanup() override;

private:

    void applyRotation(Scene* scene);

    void applyCameraRotation(Scene* scene);

    void applyMovement(Scene* scene);

    void applyCameraMovement(Scene* scene);

};

#endif
