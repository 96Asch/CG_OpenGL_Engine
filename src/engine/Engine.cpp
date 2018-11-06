#include "Engine.h"
#include "Global.h"
#include "../system/System.h"

Engine::Engine(const int &width,
               const int &height,
               const std::string &title,
               const bool &vsync) : window(Window(&input)) {
    if(!window.init(width, height, title, vsync)) {
        fprintf(stderr, "%s\n", "Windows failed to initialize!");
        exit(-1);
    }
}

Engine::~Engine(){
    for(auto system : systems)
        delete system;
}

void Engine::init() {
    scene = new Scene();
    for(auto system : systems)
        system->init();
}

void Engine::run() {
    unsigned int time = SDL_GetTicks(),
                 newtime;
    float delta;
    while(window.isRunning()) {
        newtime = SDL_GetTicks();
		delta = (float) (newtime - time);
		time = newtime;

        update(delta);
    }

}

void Engine::update(const float &delta) {
    for(auto system : systems)
        system->update(delta, scene);
    window.update();
}

void Engine::cleanup() {
    for(auto system : systems)
        system->cleanup();
    window.cleanup();
    delete scene;
}

void Engine::add(System *system) {
    systems.push_back(system);
    system->setEngine(this);
}

InputHandler* Engine::getInputHandler() {
    return &input;
}
