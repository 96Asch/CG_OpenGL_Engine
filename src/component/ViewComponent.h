#ifndef VIEWCOMPONENT_H_
#define VIEWCOMPONENT_H_

#include <glm/vec3.hpp>

struct ViewComponent : public Component {

    ViewComponent(const glm::vec3 &position,
                  const glm::vec3 &target,
                  const glm::vec3 &up)
                  : Component(CompType::VIEW),
                    position(position),
                    target(target),
                    up(up)
                    {};

    ViewComponent(const ViewComponent &view)
                  : Component(CompType::VIEW),
                    position(view.position),
                    target(view.target),
                    up(view.up)
                    {};

    ViewComponent()
                  : Component(CompType::VIEW),
                  position(glm::vec3(0.0f)),
                  target(glm::vec3(0.0f, 0.0f, -1.0f)),
                  up(glm::vec3(0.0f, 1.0f, 0.0f))
                  {};

    glm::vec3 position;

    glm::vec3 target;

    glm::vec3 up;
};

#endif
