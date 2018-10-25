#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <vector>
#include "System.h"
#include "../graphic/mesh/FlatMesh.h"

class Renderer;
class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void update(const float &delta) override;

    virtual void init() override;

    virtual void cleanup() override;
private:

    std::vector<Renderer*> renderers;

    void render();
};

#endif
