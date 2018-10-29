#ifndef INPUTSYSTEM_H_
#define INPUTSYSTEM_H_

#include "System.h"

class InputSystem : public System {

public:

    InputSystem();

    virtual ~InputSystem() override;

    virtual void init() override;

    virtual void update(const float &delta) override;

    virtual void cleanup() override;

private:

};

#endif
