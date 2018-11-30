#include "VaoFactory.h"


#define SIZE_3D 3
#define SIZE_2D 2

namespace Factory {

    VaoFactory* VAO = nullptr;

    VaoFactory::VaoFactory() { VAO = this; }

    VaoFactory::~VaoFactory() {
        for(auto vao : vaos) {
            vao.second->remove();
        }
        vaos.clear();
    }

    void VaoFactory::createVao(const std::string &source,
                               const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices) {
        auto it = vaos.find(source);
        if(it == vaos.end()) {
            auto vao = Vao::create();
            vao->bind();
            vao->createIndexBuffer(&indices[0], indices.size());
            vao->createAttribute(0, SIZE_3D, &position[0], position.size());
            vao->unbind();
            vaos[source] = std::move(vao);
        }
    }

    void VaoFactory::createVao(const std::string &source,
                               const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &texture) {
        auto it = vaos.find(source);
        if(it == vaos.end()) {
            auto vao = Vao::create();
            vao->bind();
            vao->createIndexBuffer(&indices[0], indices.size());
            vao->createAttribute(0, SIZE_3D, &position[0], position.size());
            vao->createAttribute(1, SIZE_2D, &texture[0], texture.size());
            vao->unbind();
            vaos[source] = std::move(vao);
        }
    }

    void VaoFactory::createVao(const std::string &source,
                               const std::vector<GLfloat> &position,
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &texture,
                               const std::vector<GLfloat> &normals) {
        auto it = vaos.find(source);
        if(it == vaos.end()) {
            auto vao = Vao::create();
            vao->bind();
            vao->createIndexBuffer(&indices[0], indices.size());
            vao->createAttribute(0, SIZE_3D, &position[0], position.size());
            vao->createAttribute(1, SIZE_2D, &texture[0], texture.size());
            vao->createAttribute(2, SIZE_3D, &normals[0], normals.size());
            vao->unbind();
            vaos[source] = std::move(vao);
        }
    }


    std::shared_ptr<Vao> VaoFactory::getVao(const std::string &source) {
        return vaos[source];
    }

    bool VaoFactory::isLoaded(const std::string &source) const {
        return (vaos.find(source) != vaos.end());
    }

    // void VaoFactory::getCubeVertices(const float &size,
    //                                  std::vector<GLfloat> &vertices,
    //                                  std::vector<GLuint> &indices) {
    //     vertices.clear();
    //     indices.clear();
    //     vertices.
    // }

}
