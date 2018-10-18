#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include "System.h"
#include "../graphic/mesh/FlatMesh.h"

class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void update(const float &delta) override;

    virtual void init() override;

    virtual void cleanup() override;
private:

    void render();
    FlatMesh* mesh;

};

#endif
