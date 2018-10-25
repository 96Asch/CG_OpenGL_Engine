#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <unordered_map>
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

    std::unordered_map<std::string, Renderer*> shaders;

    void render();

    FlatMesh* mesh;

};

#endif
