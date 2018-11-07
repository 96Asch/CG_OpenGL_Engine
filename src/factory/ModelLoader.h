#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include <vector>
#include <string>
#include "Global.h"

namespace Factory {

    struct ModelData {
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        std::vector<GLfloat> textures;
        std::vector<GLfloat> normals;
        GLfloat furthest;
    };


    bool loadOBJ(const std::string &file, ModelData &data);

}

#endif
