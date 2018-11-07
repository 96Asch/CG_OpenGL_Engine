#include "Engine.h"
#include "Global.h"
#include "Scene.h"
#include "../system/System.h"
#include "../system/GraphicSystem.h"

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
    const int TPS = 25;
    const int SKIP_TICKS = 1000 / TPS;
    const int MAX_FRAMESKIP = 5;

    Uint32 nextTick = SDL_GetTicks();
    int loops;
    float interpolation;

    while (window.isRunning()) {

        loops = 0;

        while (SDL_GetTicks() > nextTick && loops < MAX_FRAMESKIP) {
            update();
            nextTick += SKIP_TICKS;
            ++loops;
        }

        interpolation = (float) (SDL_GetTicks() + SKIP_TICKS - nextTick)
                        / (float) (SKIP_TICKS);
        render(interpolation);
        window.update();
    }
}

void Engine::update() {
    for(auto system : systems)
        system->update(scene);
}

void Engine::render(const float &interpolation) {
    for(auto system : systems)
        system->render(interpolation, scene);
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
