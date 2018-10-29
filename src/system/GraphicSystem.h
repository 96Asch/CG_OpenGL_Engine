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

    virtual void update(const float &delta, Scene* scene) override;

    virtual void cleanup() override;
private:

    std::vector<Renderer*> renderers;

    void render(Scene *scene);
};

#endif
