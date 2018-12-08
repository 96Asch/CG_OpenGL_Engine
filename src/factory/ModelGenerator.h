#ifndef MODELGENERATOR_H_
#define MODELGENERATOR_H_

#include <string>
#include <glm/vec3.hpp>

namespace Factory {

    void generateTerrain(const std::string &file,
                         const float &size,
                         const float &terrainHeight);


    void generateCube(const std::string &id, const float &size);


    void generateQuad(const std::string &id, const float &size);

}

#endif
