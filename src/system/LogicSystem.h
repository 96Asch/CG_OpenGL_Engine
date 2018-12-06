#ifndef LOGICSYSTEM_H_
#define LOGICSYSTEM_H_

#include "System.h"

class LogicSystem : public System {

public:

    LogicSystem();

    virtual ~LogicSystem() override;

    virtual void init() override;

    virtual void updateStep(const float &tps, Scene* scene) override;

    virtual void cleanup() override;

};

#endif
