#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"
#include "Components.h"
#include "../../factory/TextureFactory.h"
#include "../../factory/VaoFactory.h"

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

    glm::mat4 model;

    void buildModelMatrix(const TransformComponent* transform);

    virtual void preRender() override;

    virtual void postRender() override;

protected:

    virtual void init() override;

    virtual void cleanup() override;

};

#endif
