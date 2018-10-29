#include <iostream>
#include "Global.h"
#include "engine/Engine.h"
#include "Systems.h"

std::string Global::resources = "resources/";
float Global::fov = 70.0f;
float Global::aspectRatio = 800.0f/600.0f;
float Global::nearPlane = 0.1f;
float Global::farPlane = 100.0f;

int main(void) {
    Engine engine(800, 600, "First screen!", true);
    engine.add(new InputSystem());
    engine.add(new GraphicSystem());
    engine.init();
    engine.run();
    engine.cleanup();
    return 0;
}
