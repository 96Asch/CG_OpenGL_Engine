#include <iostream>
#include "engine/Engine.h"
#include <string>

int main(void) {
    Engine engine;
    if(!engine.init(800, 600, "First screen!", true)) {
        fprintf(stderr, "%s\n", "Failed to initialize the engine");
        return -1;
    }

    engine.run();
    engine.cleanup();

    return 0;
}
