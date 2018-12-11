#ifndef HDRRENDERER_H_
#define HDRRENDERER_H_

#include "Renderer.h"

class Scene;
class HdrRenderer : public Renderer {

public:

    HdrRenderer();

    ~HdrRenderer();

    virtual void init() override;

    virtual void render(TransMat &transform,
                        const std::shared_ptr<Scene> &scene) override;

    virtual void cleanup() override;

private:

};

#endif
