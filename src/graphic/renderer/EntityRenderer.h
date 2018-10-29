#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"
#include "Components.h"
#include "../../factory/TextureFactory.h"
#include "../../factory/VaoFactory.h"

struct Camera;
class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void render() override;

private:

    TextureFactory t;
    VaoFactory v;

    ModelComponent* mod;
    MaterialComponent* mat;
    TransformComponent* tran;

    glm::mat4 model, view, projection;

    virtual void preRender() override;

    virtual void postRender() override;

    void buildModelMatrix(const TransformComponent* transform);

    void buildViewMatrix(const Camera &camera);

    void buildProjectionMatrix();

protected:

    virtual void init() override;

    virtual void cleanup() override;

};

#endif
