#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "System.h"

class Scene;
class InputHandler;

struct ActionComponent;
struct MouseComponent;

class InputSystem : public System {

public:

    InputSystem();

    virtual ~InputSystem() override;

    virtual void init() override;

    virtual void update(Scene* scene) override;

    virtual void cleanup() override;

private:

    InputHandler* inputHandler;

    void handleMouse(MouseComponent* mouse);

    void handleKeys(ActionComponent* action);

};

#endif