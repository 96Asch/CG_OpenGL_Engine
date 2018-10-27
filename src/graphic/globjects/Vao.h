#ifndef VAO_H_
#define VAO_H_
#include <vector>
#include "Global.h"
#include "Vbo.h"

class Vao {

public:

    ~Vao();

    static Vao* create();

    int getIndexCount();

    template <typename... Args>
    void bind(Args... args);

    template <typename... Args>
    void unbind(Args ...args);

    void createIndexBuffer(GLuint* indices, const GLsizei &size);


    void createAttribute(const int &attribute, const GLsizei &dimension,
                         GLfloat* data, const GLsizeiptr &dataSize);

    void createAttribute(const int &attribute, const GLsizei &dimension,
                         GLuint* data, const GLsizeiptr &dataSize);

    void addInstancedAttribute(Vbo* vbo,
                               const int &attribute,
                               const GLsizei &datasize,
                               const GLsizei &instancedLength,
                               const GLsizei &offset);

    void remove();

    void bind();
    void unbind();

private:
    GLuint id;
    std::vector<Vbo*> vbos;
	Vbo* indexVbo;
	int indexCount;

    Vao(const GLuint &id);
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
