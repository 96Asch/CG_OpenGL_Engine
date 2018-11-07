#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <vector>
#include "System.h"

class Scene;
class Renderer;
class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void init() override;

    void render(const float &interpolation, Scene *scene);

    virtual void cleanup() override;

private:

    std::vector<Renderer*> renderers;

};

#endif
