#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include "Window.h"
#include "Scene.h"

class System;

class Engine {

public:
    Engine(const int &width,
           const int &height,
           const std::string &title,
           const bool &vsync);
    ~Engine();

    void init();

    void run();
    void update(const float &delta);
    void cleanup();
    void add(System* system);

private:
    std::vector<System*> systems;
    Scene* scene;
    bool isRunning;
    Window window;
};

#endif
