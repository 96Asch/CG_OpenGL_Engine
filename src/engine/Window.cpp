#include "Window.h"
#include <iostream>

Window::Window(){}

Window::~Window(){}


bool Window::init(const int &width,
                  const int &height,
                  const std::string &title,
                  const bool &vsync) {
    glfwSetErrorCallback(errorCallback);

    if (!glfwInit()) {
        glfwTerminate();
        return false;
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!window) {
        glfwTerminate();
        return false;
    }

    const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);

    setVsync(vsync);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    return true;
}

void Window::update() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Window::cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(window);
}

void Window::setVsync(const bool &vsync) {
    glfwSwapInterval(vsync);
}

GLFWwindow* Window::getWindow() {
    return window;
}

std::string Window::getTitle() const {
    return title;
}

void Window::errorCallback(int, const char* desc) {
    fprintf(stderr, "Error: %s\n", desc);
}
