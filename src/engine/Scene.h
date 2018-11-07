#ifndef SCENE_H_
#define SCENE_H_

#include "Components.h"
#include "Camera.h"


class Scene {

public:

    Scene();

    ~Scene();

    Camera& getCamera();

    ModelComponent* mod;
    MaterialComponent* mat;
    TransformComponent* tran;

private:

    Camera camera;
};

#endif
