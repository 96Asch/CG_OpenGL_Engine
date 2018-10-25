#ifndef RENDERER_H_
#define RENDERER_H_

class Renderer {

public:

    virtual void render() = 0;

private:

    virtual void cleanup() = 0;

    virtual void init() = 0;
};

#endif RENDERER_H_
