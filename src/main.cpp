#include <iostream>
#include "Global.h"
#include "engine/Engine.h"
#include "Systems.h"

std::string Global::resources;

int Global::height;
int Global::width;

int Global::targetFPS;
int Global::targetUPS;

float Global::fov;
float Global::aspectRatio;
float Global::nearPlane;
float Global::farPlane;

int main(void) {
    Global::resources = "resources/";
    Global::height = 600;
    Global::width = 800;
    Global::targetFPS = 60;
    Global::targetUPS = 60;
    Global::fov = 70.0f;
    Global::aspectRatio = Global::width / Global::height;
    Global::nearPlane = 0.1f;
    Global::farPlane = 100.0f;

    Engine engine(Global::width, Global::height, "First screen!", true);
    engine.add(new InputSystem());
    engine.add(new GraphicSystem());
    engine.init();
    engine.run();
    engine.cleanup();
    return 0;
}
