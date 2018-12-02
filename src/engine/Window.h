#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>

#include "Global.h"
#include "../input/InputHandler.h"

class GLFWwindow;

class Window {

public:

    Window();

    ~Window();

    bool init(const int &width,
              const int &height,
              const std::string &title);

    void update();

    void cleanup();

    bool isRunning() const;

    static void keyCallback(GLFWwindow* window,
                            int key,
                            int scancode,
                            int action,
                            int mods);

    static void mouseCursorCallback(GLFWwindow* window,
                                    double xpos,
                                    double ypos);

    static void mouseButtonCallback(GLFWwindow* window,
                                    int button,
                                    int action,
                                    int mods);


    GLFWwindow* getWindow();

    std::string getTitle() const;

    void setTitle(const std::string &title);

private:

    GLFWwindow* window;
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
