#include "CameraWrapper.h"

CameraWrapper::CameraWrapper(const Camera* c,
                             const Position* p,
                             const LookAt* l,
                             const Rotation* r)
                            : target(l->interpolated),
                              position(p->interpolated),
                              up(c->interpolatedUp),
                              rotation(r->interpolated)
                              {}

CameraWrapper::~CameraWrapper() {}

void CameraWrapper::setPosition(const glm::vec3 &position) {
    this->position = position;
}

void CameraWrapper::lookAt(glm::vec3 up,
                           const float &yaw,
                           const float &pitch)
{
    this->rotation.x = pitch;
    this->rotation.y = yaw;
    target.x = -cos(glm::radians(pitch)) *
                    sin(glm::radians(yaw));
    target.y = -sin(glm::radians(pitch));
    target.z = -cos(glm::radians(yaw)) *
                    cos(glm::radians(pitch));
    target = glm::normalize(target);
    glm::vec3 right = glm::normalize(glm::cross(target, up));
    up = glm::normalize(glm::cross(right, target));
}

void CameraWrapper::invertPitch() {
    this->rotation.x = -this->rotation.x;
}

glm::vec3 CameraWrapper::getTarget() {
    return target;
}

glm::vec3 CameraWrapper::getPosition() {
    return position;
}

glm::vec3 CameraWrapper::getUp() {
    return up;
}

glm::mat4 CameraWrapper::getViewMatrix() {
    glm::mat4 view = glm::mat4(1.0f);
    view = glm::lookAt(
                       position,
                       position + target,
                       up
                      );
    return view;
}

glm::mat4 CameraWrapper::getProjectionMatrix(const float &fov,
                                             const float &aspect,
                                             const float &near,
                                             const float &far)
{
    return glm::perspective(
                            glm::radians(fov),
                            aspect,
                            near,
                            far
                           );
}
