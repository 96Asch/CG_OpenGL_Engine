#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <GL/gl3w.h>
#include <SDL/SDL.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/util/Util.h"
#include "../src/util/GLUtil.h"

namespace Global {
    extern std::string resources;

    extern int height, width;

    extern float fov;
    extern float aspectRatio;
    extern float nearPlane;
    extern float farPlane;

    const size_t NUM_BITS = 64;
    const size_t MAX_POINT_LIGHTS = 5;
}


#endif
