#include "Engine.h"
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
    while(window.isRunning())
        update(1.0);
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
}
