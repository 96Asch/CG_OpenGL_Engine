#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "System.h"

class Scene;
class InputHandler;
struct InputComponent;
class InputSystem : public System {

public:

    InputSystem();

    virtual ~InputSystem() override;

    virtual void init() override;

    virtual void update(Scene* scene) override;

    virtual void cleanup() override;

private:

    InputHandler* inputHandler;

    void handleKeys(InputComponent* input);

};

#endif
