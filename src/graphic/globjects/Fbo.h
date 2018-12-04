#ifndef FBO_H_
#define FBO_H_

#include <memory>

#include "Global.h"

class Fbo {

public:

    Fbo(const GLuint &id,
        const unsigned &colorUnit,
        const unsigned &width,
        const unsigned &height);

    ~Fbo();

    static std::shared_ptr<Fbo> create(const unsigned &colorUnit,
                                       const unsigned &width,
                                       const unsigned &height);

    void bind(const unsigned &width, const unsigned &height);

    void unbind();

    void remove();

    GLuint getColorTexture();

    GLuint getDepthTexture();

private:

    GLuint id;
    GLuint depthBuffer;

    GLuint depthTexture;
    GLuint colorTexture;

    void initTexture(const unsigned &colorUnit,
                     const unsigned &width,
                     const unsigned &height);

    void initDepthTexture(const unsigned &width,
                          const unsigned &height);

    void initDepthBuffer(const unsigned &width,
                         const unsigned &height);

};


#endif
