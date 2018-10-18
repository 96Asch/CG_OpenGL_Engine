#include "Engine.h"

Engine::Engine(){}

Engine::~Engine(){}

bool Engine::init(const int &width,
                  const int &height,
                  const std::string &title,
                  const bool &vsync) {
    if(!window.init(width, height, title, vsync))
        return false;

    return true;
}

void Engine::run() {
    while(!window.shouldClose())
        update(1.0);
}

void Engine::update(const float &delta) {


    window.update();
}

void Engine::cleanup() {

}

void Engine::add(System *system) {

}
