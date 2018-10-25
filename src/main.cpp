#include <iostream>
#include "Global.h"
#include "engine/Engine.h"
#include "system/GraphicSystem.h"

std::string Global::resources = "../resources/";

int main(void) {
    Engine engine(800, 600, "First screen!", true);

    engine.add(new GraphicSystem());

    engine.init();
    engine.run();
    engine.cleanup();
    return 0;
}
