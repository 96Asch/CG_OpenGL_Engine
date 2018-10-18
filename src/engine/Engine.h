#ifndef ENGINE_H_
#define ENGINE_H_

#include <vector>
#include "Window.h"

class System;
class Engine {

public:
    Engine();
    ~Engine();

    bool init(const int &width,
              const int &height,
              const std::string &title,
              const bool &vsync);

    void run();
    void update(const float &delta);
    void cleanup();
    void add(System* system); 

private:
    std::vector<System*> systems;

    Window window;
    bool isRunning;


};

#endif
