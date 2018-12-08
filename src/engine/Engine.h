#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include <memory>

#include "Window.h"
#include "../factory/TextureFactory.h"
#include "../factory/VaoFactory.h"
#include "../factory/FboFactory.h"

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

    void update(const float &TPS);

    void render(const float &interpolation);

    template <typename T, typename... Args>
    void add(Args... args);

private:
    std::vector<std::unique_ptr<System>> systems;
    Window window;
    std::shared_ptr<Scene> scene;

    Factory::TextureFactory t;
    Factory::VaoFactory v;
    Factory::FboFactory f;

    Input::InputHandler input;

    void cleanup();
};

template <typename T, typename... Args>
void Engine::add(Args... args) {
    systems.push_back(std::make_unique<T>(args...));
}

#endif
