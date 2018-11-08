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
    const int TPS = 30;
    const int SKIP_TICKS = 1000 / TPS;
    const int MAX_FRAMESKIP = 5;

    Uint32 currentTick = SDL_GetTicks(), nextTick;
    int loops;
    float interpolation;

    while (window.isRunning()) {
        nextTick = SDL_GetTicks();
        loops = 0;

        while (nextTick > currentTick && loops < MAX_FRAMESKIP) {
            update();
            currentTick += SKIP_TICKS;
            ++loops;

        }

        interpolation = (float) (nextTick + SKIP_TICKS - currentTick)
                        / (float) (SKIP_TICKS);
        render(interpolation);
        window.update();
    }
}

void Engine::update() {
    window.pollEvents();
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
