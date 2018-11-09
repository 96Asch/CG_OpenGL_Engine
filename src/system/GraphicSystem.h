#ifndef GRAPHICSYSTEM_H_
#define GRAPHICSYSTEM_H_

#include <vector>
#include "System.h"
#include <glm/mat4x4.hpp>

class Scene;
class Renderer;

struct Camera;

class GraphicSystem : public System {

public:
    GraphicSystem();

    virtual ~GraphicSystem() override;

    virtual void init() override;

    void render(const float &interpolation, Scene *scene);

    virtual void cleanup() override;

private:

    std::vector<Renderer*> renderers;

    glm::mat4 view, projection;

    void buildViewMatrix(const float &interpolation, const Camera &camera);

    void buildProjectionMatrix();

    template <typename T>
    T lerp(const T &start, const T &end, const float &alpha);

};

template <typename T>
T GraphicSystem::lerp(const T &start, const T &end, const float &alpha) {
    return (start * (1 - alpha) + end * alpha);
}

#endif
