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

    void bind(int attribs...);

    void unbind(int attribs...);

    void createIndexBuffer(int* indices, const GLsizei &size);

    template <typename T>
    void createAttribute(const int &attribute, const GLsizei &attribSize,
                              T* data, const GLsizei &size) {
        Vbo* vbo = Vbo::create(GL_ARRAY_BUFFER);
    	vbo->bind();
    	vbo->storeData<T>(data, size);
    	glVertexAttribPointer(attribute, attribSize, GL_FLOAT,
                              false, attribSize * BYTES_PER_FLOAT, 0);
    	vbo->unbind();
    	vbos.push_back(vbo);
    }

    void createAttribute(const int &attribute,
                         const GLsizei &attribSize,
                         int* data,
                         const GLsizei &size);

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

#endif
