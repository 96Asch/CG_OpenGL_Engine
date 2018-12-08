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

    virtual void updateStep(const float &tps, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;

private:

    void handleMouse(std::shared_ptr<Scene> scene);

    void handleKeys(std::shared_ptr<Scene> scene);

};

#endif
