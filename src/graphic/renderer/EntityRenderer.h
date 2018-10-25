#ifndef ENTITYRENDERER_H_
#define ENTITYRENDERER_H_

#include "Renderer.h"

class EntityRenderer : public Renderer {

public:

    virtual void render();

private:



    virtual void init();

    virtual void cleanup();

}

#endif
