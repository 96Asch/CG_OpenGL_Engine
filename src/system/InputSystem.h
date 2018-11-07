#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "System.h"
#include "../input/InputHandler.h"

class Scene;
class InputSystem : public System {

public:

    InputSystem();

    virtual ~InputSystem() override;

    virtual void init() override;

    virtual void update(Scene* scene) override;

    virtual void cleanup() override;

private:

    InputHandler* input;

    void handleKeys(Scene* scene);

};

#endif
