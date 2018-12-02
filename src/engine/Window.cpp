#include "Window.h"
#include <iostream>

Window::Window() {}

Window::~Window(){
    glfwTerminate();
}

bool Window::init(const int &width,
                  const int &height,
                  const std::string &title) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit())
        return false;

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!window) {
        return false;
    }

    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);
    glfwMakeContextCurrent(window);

    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return false;
    }
    if (!gl3wIsSupported(4, 3)) {
        fprintf(stderr, "OpenGL 4.3 not supported\n");
        return false;
    }
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
             glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseCursorCallback);
    glfwSetKeyCallback(window, keyCallback);
    glfwShowWindow(window);
    return true;
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::cleanup() {
    glfwDestroyWindow(window);
}

bool Window::isRunning() const {
    return !glfwWindowShouldClose(window);
}

void Window::keyCallback(GLFWwindow*,
                         int key,
                         int,
                         int action,
                         int)
{
    if(action == GLFW_PRESS)
        Input::INPUT->pressKey(key);
    else if(action == GLFW_RELEASE)
        Input::INPUT->releaseKey(key);
}

void Window::mouseButtonCallback(GLFWwindow*,
                                 int button,
                                 int action,
                                 int)
{
    if(action == GLFW_PRESS)
        Input::INPUT->clickMouse(button);
    else if(action == GLFW_RELEASE)
        Input::INPUT->releaseMouse(button);
}

void Window::mouseCursorCallback(GLFWwindow*, double xpos, double ypos) {
    Input::INPUT->onMouseMoved(xpos, ypos);
}

GLFWwindow* Window::getWindow() {
    return window;
}

std::string Window::getTitle() const {
    return title;
}

void Window::setTitle(const std::string &newTitle) {
     glfwSetWindowTitle(window, newTitle.c_str());
}

void Window::errorCallback(int i, const char* desc) {
    fprintf(stderr, "Error %i: %s\n", i, desc);
}

void Window::MessageCallback(GLenum,
                             GLenum type,
                             GLuint,
                             GLenum severity,
                             GLsizei,
                             const GLchar* message,
                             const void*)
{
  fprintf( stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           ( type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "" ),
            type, severity, message );
}
