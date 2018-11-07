#include "VaoFactory.h"


#define SIZE_3D 3
#define SIZE_2D 2

namespace Factory {

    VaoFactory::VaoFactory() = default;

    VaoFactory::~VaoFactory() {
        for(auto vao : vaos) {
            vao->remove();
            delete vao;
        }
    }

    Vao* VaoFactory::createVao(const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices) {
        Vao* vao = Vao::create();
        vao->bind();
        vao->createIndexBuffer(&indices[0], indices.size());
        vao->createAttribute(0, SIZE_3D, &position[0], position.size());
        vao->unbind();
        vaos.push_back(vao);
        return vao;
    }

    Vao* VaoFactory::createVao(const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &texture) {
        Vao* vao = Vao::create();
        vao->bind();
        vao->createIndexBuffer(&indices[0], indices.size());
        vao->createAttribute(0, SIZE_3D, &position[0], position.size());
        vao->createAttribute(1, SIZE_2D, &texture[0], texture.size());
        vao->unbind();
        vaos.push_back(vao);
        return vao;
    }

    Vao* VaoFactory::createVao(const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &texture,
                               const std::vector<GLfloat> &normals) {
        Vao* vao = Vao::create();
        vao->bind();
        vao->createIndexBuffer(&indices[0], indices.size());
        vao->createAttribute(0, SIZE_3D, &position[0], position.size());
        vao->createAttribute(1, SIZE_2D, &texture[0], texture.size());
        vao->createAttribute(2, SIZE_3D, &normals[0], normals.size());
        vao->unbind();
        vaos.push_back(vao);
        return vao;
    }
    
}
