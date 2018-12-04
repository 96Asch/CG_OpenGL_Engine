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
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &position)
    {
        if(!isLoaded(source)) {
            auto vao = Vao::create();
            vao->bind();
            vao->createIndexBuffer(&indices[0], indices.size());
            vao->createAttribute(0, SIZE_3D, &position[0], position.size());
            vao->unbind();
            vaos[source] = std::move(vao);
        }
    }

    void VaoFactory::createVao(const std::string &source,
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &position,
                               const std::vector<GLfloat> &texture)
    {
        if(!isLoaded(source)) {
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
                               const std::vector<GLuint> &indices,
                               const std::vector<GLfloat> &position,
                               const std::vector<GLfloat> &texture,
                               const std::vector<GLfloat> &normals)
    {
        if(!isLoaded(source)) {
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
        if(isLoaded(source))
            return vaos[source];
        throw std::runtime_error("Error: cannot find vao for: " + source);
        return nullptr;
    }

    bool VaoFactory::isLoaded(const std::string &source) const {
        return (vaos.find(source) != vaos.end());
    }

}
