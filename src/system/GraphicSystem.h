#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <vector>
#include <memory>
#include <glm/mat4x4.hpp>

#include "System.h"
#include "../util/TransMat.h"
#include "../graphic/renderer/HdrRenderer.h"

class Scene;
class Renderer;

struct Camera;

class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void init() override;

    void renderStep(const float &interpolation, std::shared_ptr<Scene> scene);

    virtual void cleanup() override;

private:

    std::vector<std::unique_ptr<Renderer>> bufferRenderers;
    std::vector<std::unique_ptr<Renderer>> screenRenderers;
    HdrRenderer hRenderer;
    std::vector<std::unique_ptr<Renderer>> forwardRenderers;

    TransMat transform;

    void geometryPass(const std::shared_ptr<Scene> &scene);

    void lightingPass(const std::shared_ptr<Scene> &scene);

    void postProcessPass(const std::shared_ptr<Scene> &scene);

    void forwardPass(const std::shared_ptr<Scene> &scene);

    void buildViewMatrix(std::shared_ptr<Scene> scene);

    void buildProjectionMatrix();

    void interpolationStep(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolatePositions(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolateRotations(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolateScales(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolateExplosions(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolateLookAt(const float &interpolation, std::shared_ptr<Scene> scene);

    void interpolateCamera(const float &interpolation, std::shared_ptr<Scene> scene);
};

#endif
