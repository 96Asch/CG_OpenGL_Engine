#ifndef PHYSICSSYSTEM_H_
#define PHYSICSSYSTEM_H_

#include "System.h"

class Scene;

struct InputComponent;
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
    
    void applyMovement(InputComponent* input, ViewComponent* view, VelocityComponent* velocity);

};

#endif
