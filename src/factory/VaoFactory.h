#ifndef VAOFACTORY_H_
#define VAOFACTORY_H_

#include <map>
#include <memory>
#include <string>

#include "../graphic/globjects/Vao.h"

namespace Factory {

    class VaoFactory;
    
    extern VaoFactory* VAO;

    class VaoFactory {

    public:

        VaoFactory();
        ~VaoFactory();

        void createVao(const std::string &source,
                       const std::vector<GLuint> &indices,
                       const std::vector<GLfloat> &position);

        void createVao(const std::string &source,
                       const std::vector<GLuint> &indices,
                       const std::vector<GLfloat> &position,
                       const std::vector<GLfloat> &texture);

        void createVao(const std::string &source,
                       const std::vector<GLuint> &indices,
                       const std::vector<GLfloat> &position,
                       const std::vector<GLfloat> &texture,
                       const std::vector<GLfloat> &normals);

        void removeVao();

        std::shared_ptr<Vao> getVao(const std::string &source);

        bool isLoaded(const std::string &source) const;

    private:

        std::map<std::string, std::shared_ptr<Vao>> vaos;

        // void getCubeVertices(const float &size,
        //                      std::vector<GLfloat> &vertices);

    };

};

#endif
