#ifndef VAOFACTORY_H_
#define VAOFACTORY_H_

#include <vector>

#include "../graphic/globjects/Vao.h"

namespace Factory {

    class VaoFactory;
    extern VaoFactory* VAO;

    class VaoFactory {

    public:

        VaoFactory();
        ~VaoFactory();

        Vao* createVao(const std::vector<GLfloat> &position,
                       const std::vector<GLuint> &indices);

        Vao* createVao(const std::vector<GLfloat> &position,
                       const std::vector<GLuint> &indices,
                       const std::vector<GLfloat> &texture);

        Vao* createVao(const std::vector<GLfloat> &position,
                       const std::vector<GLuint> &indices,
                       const std::vector<GLfloat> &texture,
                       const std::vector<GLfloat> &normals);

        void removeVao();

    private:

        std::vector<Vao*> vaos;


    };

};

#endif
