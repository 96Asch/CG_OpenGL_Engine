#ifndef CAMERAWRAPPER_H_
#define CAMERAWRAPPER_H_

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Components.h"

class CameraWrapper {

public:

    CameraWrapper(const Camera* c,
                  const Position* p,
                  const LookAt* l,
                  const Rotation* r);

    ~CameraWrapper();

    void setPosition(const glm::vec3 &position);

    void lookAt(glm::vec3 up, const float &yaw, const float &pitch);

    void invertPitch();

    glm::vec3 getTarget();

    glm::vec3 getPosition();

    glm::vec3 getUp();

    glm::mat4 getViewMatrix();

    glm::mat4 getProjectionMatrix(const float &fov,
                                  const float &aspect,
                                  const float &near,
                                  const float &far);

private:

    glm::vec3 target;
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 rotation;

};

#endif
