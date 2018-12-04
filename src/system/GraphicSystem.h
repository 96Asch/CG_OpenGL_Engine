#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <vector>
#include <glm/mat4x4.hpp>

#include "System.h"
#include "../util/TransMat.h"

class Scene;
class Renderer;

struct Camera;

class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void init() override;

    void renderStep(const float &interpolation, Scene* scene);

    virtual void cleanup() override;

private:

    std::vector<Renderer*> renderers;

    TransMat transform;

    void buildViewMatrix(Scene* scene);

    void buildProjectionMatrix();

    void interpolatePositions(const float &interpolation, Scene *scene);

    void interpolateRotations(const float &interpolation, Scene *scene);

    void interpolateScales(const float &interpolation, Scene *scene);

    void interpolateCamera(const float &interpolation, Scene* scene);
};

#endif
