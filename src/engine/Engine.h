#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>

#include "Window.h"
#include "../factory/TextureFactory.h"
#include "../factory/VaoFactory.h"

class System;
class Scene;

class Engine {

public:
    Engine(const int &width,
           const int &height,
           const std::string &title);

    ~Engine();

    void loadSetup(const std::string &file);

    void init();

    void run();

    void update();

    void render(const float &interpolation);

    void cleanup();

    void add(System* system);

    InputHandler* getInputHandler();

private:
    std::vector<System*> systems;
    Window window;
    Scene* scene;

    Factory::TextureFactory t;
    Factory::VaoFactory v;

    InputHandler input;
};

#endif
