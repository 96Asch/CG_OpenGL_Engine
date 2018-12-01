#include <stb_image.h>
#include <vector>

#include "ModelGenerator.h"
#include "VaoFactory.h"

namespace Factory {

    namespace {

    }

    void generateTerrain(const std::string &file, const float &size) {
        // if(!file.empty) {
        //     int w, h, components;
        //     unsigned char* image = stbi_load((Global::resources + file).c_str(),
        //                                   &w, &h, &components, STBI_rgb_alpha);
        // }
        unsigned numVertex = 64;
        unsigned count = numVertex * numVertex;
        std::vector<unsigned> indices;
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> uvs;

        for(unsigned i = 0; i < numVertex; i++){
            for(unsigned j = 0; j < numVertex; j++){

                vertices.push_back((float) j / ((float) numVertex - 1) * size);
                vertices.push_back(0);
                vertices.push_back((float) i / ((float) numVertex - 1) * size);

                normals.push_back(0);
                normals.push_back(1);
                normals.push_back(0);

                uvs.push_back((float) j / ((float) numVertex - 1));
                uvs.push_back((float) i / ((float) numVertex - 1));
            }
        }
        for(unsigned gz = 0 ; gz < numVertex - 1; gz++) {
            for(unsigned gx = 0; gx < numVertex - 1; gx++){
                unsigned topLeft = (gz * numVertex) + gx;
                unsigned topRight = topLeft + 1;
                unsigned bottomLeft = ((gz + 1) * numVertex) + gx;
                unsigned bottomRight = bottomLeft + 1;
                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }
        VAO->createVao(file, indices, vertices, uvs, normals);
    }

}
