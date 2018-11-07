#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "../engine/Engine.h"

class Scene;
class System {

public:
    System() = default;

    virtual ~System() = default;

    virtual void init() = 0;

    virtual void update(Scene*) {};

    virtual void render(const float &, Scene*) {};

    virtual void cleanup() = 0;

    void setEngine(Engine* engine) {owner = engine;};

protected:

    Engine* owner = nullptr;
};

#endif
