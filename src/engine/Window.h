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
              const std::string &title);

    void update();

    void cleanup();

    bool isRunning() const;

    void pollEvents();

    SDL_Surface* getWindow();

    std::string getTitle() const;

    void setTitle(const std::string &title);

private:

    SDL_Surface* window;
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
