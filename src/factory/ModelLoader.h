#ifndef MODELLOADER_H_
#define MODELLOADER_H_

#include <vector>
#include <string>
#include "Global.h"

class Vao;

namespace Factory {

    struct ModelData {
        std::vector<GLfloat> vertices;
        std::vector<GLuint> indices;
        std::vector<GLfloat> textures;
        std::vector<GLfloat> normals;
        GLfloat furthest;
    };

    void loadOBJ(const std::string &file);

    void generateTerrain(const unsigned &numVertex,
                         std::vector<std::vector<float>> &heights);

}

#endif
