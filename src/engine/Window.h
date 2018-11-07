#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

#include "Global.h"
#include "../input/InputHandler.h"

class Window {

public:

    Window(InputHandler* input);

    ~Window();

    bool init(const int &width,
              const int &height,
              const std::string &title,
              const bool &vsync);
    void update();

    void cleanup();

    bool isRunning() const;

    void setVsync(const bool &vsync);

    void pollEvents();

    SDL_Window* getWindow();

    std::string getTitle() const;

private:

    SDL_Window* window;
    SDL_GLContext context;
    InputHandler* input;
    bool running;
    std::string title;

    static void errorCallback(int, const char* desc);

    static void MessageCallback( GLenum source,
                                 GLenum type,
                                 GLuint id,
                                 GLenum severity,
                                 GLsizei length,
                                 const GLchar* message,
                                 const void* userParam );
};

#endif
