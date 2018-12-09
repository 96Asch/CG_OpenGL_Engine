#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "../engine/Engine.h"

class Scene;
class System {

public:
    System() = default;

    virtual ~System() = default;

    virtual void init() = 0;

    virtual void updateStep(const float &, std::shared_ptr<Scene>) {};

    virtual void renderStep(const float &, std::shared_ptr<Scene>) {};

    virtual void cleanup() = 0;

protected:

};

#endif
