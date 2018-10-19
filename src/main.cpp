#include <iostream>
#include "Global.h"
#include "engine/Engine.h"
#include "system/GraphicSystem.h"

std::string Global::resources = "../resources/";

int main(void) {
    Engine engine;

    engine.add(new GraphicSystem());
    if(!engine.init(800, 600, "First screen!", true)) {
        fprintf(stderr, "%s\n", "Failed to initialize the engine");
        return -1;
    }

    engine.run();
    engine.cleanup();

    return 0;
}
