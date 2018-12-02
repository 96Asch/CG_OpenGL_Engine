#include <stb_image.h>
#include <vector>
#include <iostream>

#include "ModelGenerator.h"
#include "VaoFactory.h"

#define PIXELS (256 * 256 * 256)

namespace Factory {


    float fromHeightMap(const unsigned char* image,
                        const int &width,
                        const int &height,
                        const float &terrainHeight,
                        const int &x,
                        const int &y)
    {
        if(!image || ((x < 0 || x >= width ) || (y < 0 || y >= height)))
            return 0.0f;
        unsigned bytePerPixel = STBI_rgb_alpha;
        const unsigned char* pixelOffset = image + (x + height * y) * bytePerPixel;
        const unsigned rgb = pixelOffset[0] + pixelOffset[1] + pixelOffset[2];
        float value = (float) rgb / 3.0f;
        value /= 256.0f;
        value -= 0.5f;
        value *= terrainHeight;
        return value;
    }

    glm::vec3 getNormal(unsigned char* image,
                        const int &width,
                        const int &height,
                        const float &terrainHeight,
                        const int &x,
                        const int &y)
    {
        float hUp = fromHeightMap(image, width, height, terrainHeight, x, y+1);
        float hDo = fromHeightMap(image, width, height, terrainHeight, x, y-1);
        float hL = fromHeightMap(image, width, height, terrainHeight, x-1, y);
        float hR = fromHeightMap(image, width, height, terrainHeight, x+1, y);
        glm::vec3 normal = glm::vec3(hL - hR, 2.0f, hDo - hUp);
        glm::normalize(normal);
        return normal;
    }

    void generateTerrain(const std::string &file,
                         const float &size,
                         const float &terrainHeight)
    {
        unsigned numVertex = 64;
        unsigned char* image = nullptr;
        int w(0), h(0);
        if(!file.empty()) {
            int components;
            image = stbi_load((Global::resources + file).c_str(),
                                          &w, &h, &components, STBI_rgb_alpha);
            numVertex = h;
        }
        unsigned count = numVertex * numVertex;
        std::vector<unsigned> indices;
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> uvs;

        for(unsigned i = 0; i < numVertex; i++){
            for(unsigned j = 0; j < numVertex; j++){

                vertices.push_back((float) j / ((float) numVertex - 1) * size);
                vertices.push_back(fromHeightMap(image, w, h, terrainHeight, j, i));
                vertices.push_back((float) i / ((float) numVertex - 1) * size);

                glm::vec3 normal = getNormal(image, w, h, terrainHeight, j, i);
                normals.push_back(normal.x);
                normals.push_back(normal.y);
                normals.push_back(normal.z);

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
        stbi_image_free(image);
        VAO->createVao(file, indices, vertices, uvs, normals);
    }

}
