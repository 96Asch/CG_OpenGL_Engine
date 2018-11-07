#ifndef CAMERA_H_
#define CAMERA_H_

#include "Components.h"

struct Camera {

    Camera() {};

    Camera(const ViewComponent &view) : view(view) {};

    ViewComponent view;
    VelocityComponent velocity;
};

#endif
