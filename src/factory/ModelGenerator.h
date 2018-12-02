#ifndef MODELGENERATOR_H_
#define MODELGENERATOR_H_

#include <string>
#include <glm/vec3.hpp>

namespace Factory {

    float fromHeightMap(const unsigned char* image,
                        const int &width,
                        const int &height,
                        const float &terrainHeight,
                        const int &x,
                        const int &y);

    glm::vec3 getNormal(const unsigned char* image,
                        const int &width,
                        const int &height,
                        const float &terrainHeight,
                        const int &x,
                        const int &y);

    void generateTerrain(const std::string &file,
                         const float &size,
                         const float &terrainHeight);

}

#endif
