#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"
#include "../mesh/FlatMesh.h"

class EntityRenderer : public Renderer {

public:

    EntityRenderer();
    ~EntityRenderer();

    virtual void render() override;

private:

        FlatMesh* mesh;

    virtual void preRender() override;

    virtual void postRender() override;

protected:

    virtual void init() override;

    virtual void cleanup() override;

};

#endif
