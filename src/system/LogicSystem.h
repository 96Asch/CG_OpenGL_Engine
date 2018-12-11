#ifndef LOGICSYSTEM_H_
#define LOGICSYSTEM_H_

#include "System.h"

class LogicSystem : public System {

public:

    LogicSystem();

    virtual ~LogicSystem() override;

    virtual void init() override;

    virtual void updateStep(const float &tps, std::shared_ptr<Scene> scene) override;

    virtual void cleanup() override;


private:

    bool firstUpdate;
    float secondsCounter;

    void checkIntersections(std::shared_ptr<Scene> scene);

    void explodeAll(const float &tps, std::shared_ptr<Scene> scene);
};

#endif
