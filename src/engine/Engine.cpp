#include "Engine.h"
#include "Global.h"
#include "Scene.h"
#include "../system/System.h"
#include "../system/GraphicSystem.h"

Engine::Engine(const int &width,
               const int &height,
               const std::string &title)
               : scene(nullptr)
{
    if(!window.init(width, height, title)) {
        fprintf(stderr, "%s\n", "Windows failed to initialize!");
        exit(-1);
    }
}

Engine::~Engine(){
    for(auto system : systems)
        delete system;
}

void Engine::loadSetup(const std::string &file) {
    scene = new Scene();
    std::ifstream in(file);
    if(in) {
        if(scene->deserialize(in)) {
            std::cout << "Deserialization Completed" << std::endl;
            std::cout << "Loaded Entities: " << scene->getEntities().numEntities() << std:: endl;
        }
        else {
            std::cerr << "Deserialization Failed" << std::endl;
        }
    }
    else {
        std::cerr << "Could not open file: " << file << std::endl;
    }
}

void Engine::init() {
    if(!scene) {
        scene = new Scene();
    }
    for(auto system : systems)
        system->init();
}

void Engine::run() {
    const double TPS = 1.0 / 25.0;
    double lastTime = glfwGetTime(), timer = lastTime;
    double accumulator = 0, nowTime = 0;
    double frameTime = 0;
    int frames = 0 , updates = 0;

    while (window.isRunning()) {

        nowTime = glfwGetTime();
        frameTime = (nowTime - lastTime);
        if(frameTime > 0.25)
            frameTime = 0.25;
        lastTime = nowTime;

        accumulator += frameTime;

        while (accumulator >= TPS){
            update(TPS);
            updates++;
            accumulator -= TPS;
        }

        const float alpha = accumulator / TPS;
        render(alpha);
        frames++;
        window.update();

        if (glfwGetTime() - timer > 1.0) {
            timer ++;
            std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }

    }
}

void Engine::update(const float &TPS) {
    for(auto system : systems)
        system->updateStep(TPS, scene);
}

void Engine::render(const float &interpolation) {
    for(auto system : systems)
        system->renderStep(interpolation, scene);
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
