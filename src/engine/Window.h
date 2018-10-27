#ifndef WINDOW_H_
#define WINDOW_H_

#include "Global.h"
#include <string>

class Window {

public:

    Window();
    ~Window();

    bool init(const int &width,
              const int &height,
              const std::string &title,
              const bool &vsync);
    void update();
    void cleanup();

    bool shouldClose() const;
    void setVsync(const bool &vsync);

    GLFWwindow* getWindow();
    std::string getTitle() const;

    static void errorCallback(int, const char* desc);

    static void
    MessageCallback( GLenum source,
                     GLenum type,
                     GLuint id,
                     GLenum severity,
                     GLsizei length,
                     const GLchar* message,
                     const void* userParam );

private:

    GLFWwindow* window;
    std::string title;







};

#endif
