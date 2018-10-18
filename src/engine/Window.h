#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>
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
    
private:

    GLFWwindow* window;
    std::string title;







};

#endif
