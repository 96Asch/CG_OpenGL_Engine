#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"
#include "../mesh/Mesh.h"
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
        Vao* vao;
        GLuint tex;

    virtual void preRender() override;

    virtual void postRender() override;

protected:

    virtual void init() override;

    virtual void cleanup() override;

};

#endif
