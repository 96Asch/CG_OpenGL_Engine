#include <iostream>
#include <sstream>
#include <fstream>
#include "Global.h"
#include "engine/Engine.h"
#include "Systems.h"

std::string Global::resources;

int Global::height = 0;
int Global::width = 0;

float Global::fov = 0;
float Global::aspectRatio = 0;
float Global::nearPlane = 0;
float Global::farPlane = 0;

void initPrefs(const std::string &file) {
    std::ifstream in(file);
    if(in) {
        std::string line;
        while(std::getline(in, line)) {
            std::stringstream ss(line);
            std::string setting, value;
            if(std::getline(ss, setting, '=')) {
                if(setting == "screenHeight") {
                    std::getline(ss, value, '=');
                    Global::height = std::stoi(value);
                }
                else if(setting == "screenWidth") {
                    std::getline(ss, value, '=');
                    Global::width = std::stoi(value);
                }
                else if(setting == "fov") {
                    std::getline(ss, value, '=');
                    Global::fov = std::stof(value);
                }
                else if(setting == "resources") {
                    std::getline(ss, value, '=');
                    Global::resources = value;
                }
            }
        }
    }
}

void initGlobals() {
    Global::resources = Global::resources.empty() ? "resources/" : Global::resources;
    Global::width = Global::width == 0 ? 800 : Global::width;
    Global::height = Global::height == 0 ? 600 : Global::height;
    Global::fov = Global::fov == 0 ? 70.0f : Global::fov;
    Global::aspectRatio = Global::width / Global::height;
    Global::nearPlane = 0.1f;
    Global::farPlane = 1000.0f;
}

int main(int argc, char** argv) {
    initPrefs("prefs.txt");
    initGlobals();
    Engine engine(Global::width, Global::height, "First screen!");

    engine.add<InputSystem>();
    engine.add<EnvironmentSystem>();
    engine.add<PhysicsSystem>();
    engine.add<GraphicSystem>();

    if(argc == 2)
        engine.loadSetup(std::string(argv[1]));
    else
        std::cout << "No setup file specified" << std::endl;

    engine.init();
    engine.run();
    // engine.cleanup();
    return 0;
}
