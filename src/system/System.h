#ifndef SYSTEM_H_
#define SYSTEM_H_

class Scene;
class System {

public:
    System() = default;

    virtual ~System() = default;

    virtual void init() = 0;

    virtual void update(const float &delta, Scene* scene) = 0;

    virtual void cleanup() = 0;

private:



};

#endif
