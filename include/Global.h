#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../src/util/Util.h"

#define BYTES_PER_FLOAT 4
#define BYTES_PER_INT 4

namespace Global {
    extern std::string resources;

    extern float fov;
    extern float aspectRatio;
    extern float nearPlane;
    extern float farPlane;
}


#endif
