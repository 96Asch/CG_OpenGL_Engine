#ifndef VAO_H_
#define VAO_H_

#include <vector>
#include <memory>
#include "Global.h"
#include "Vbo.h"

class VaoFactory;

class Vao {

public:

    Vao(const GLuint &id);

    ~Vao();

    static std::shared_ptr<Vao> create();

    int getIndexCount();

    template <typename... Args>
    void bind(Args... args);

    template <typename... Args>
    void unbind(Args ...args);

    void createIndexBuffer(const GLuint* indices, const GLsizei &size);


    void createAttribute(const int &attribute, const GLsizei &dimension,
                         const GLfloat* data, const GLsizeiptr &dataSize);

    void createAttribute(const int &attribute, const GLsizei &dimension,
                         const GLuint* data, const GLsizeiptr &dataSize);

    void addInstancedAttribute(std::shared_ptr<Vbo> vbo,
                               const int &attribute,
                               const GLsizei &datasize,
                               const GLsizei &instancedLength,
                               const GLsizei &offset);

    void remove();

    void bind();

    void unbind();

private:
    friend class VaoFactory;

    GLuint id;
    std::vector<std::shared_ptr<Vbo>> vbos;
	std::shared_ptr<Vbo> indexVbo;
	int indexCount;
};

template <typename... Args>
void Vao::bind(Args... args) {
    bind();
    Util::pack_foreach([this](const GLint &attribute){
        glEnableVertexAttribArray(attribute);
    }, args...);
}

template <typename... Args>
void Vao::unbind(Args... args) {
    Util::pack_foreach([this](const GLint &attribute){
        glDisableVertexAttribArray(attribute);
    }, args...);
    unbind();
}
#endif
