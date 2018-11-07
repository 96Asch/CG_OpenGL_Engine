#include "Window.h"
#include <iostream>

Window::Window(InputHandler* input) :input(input), running(true) {}

Window::~Window(){
    input = nullptr;
    SDL_Quit();
}

bool Window::init(const int &width,
                  const int &height,
                  const std::string &title,
                  const bool &vsync) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
  		std::cerr << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
  		return false;
  	}

    window = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              width, height,
                              SDL_WINDOW_OPENGL);

    if(!window) {
        fprintf(stderr, "SDL failed to initialize");
        return false;
    }

    context = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


    if (gl3wInit()) {
        fprintf(stderr, "failed to initialize OpenGL\n");
        return false;
    }
    if (!gl3wIsSupported(4, 3)) {
        fprintf(stderr, "OpenGL 4.3 not supported\n");
        return false;
    }
    setVsync(vsync);
    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
                glGetString(GL_SHADING_LANGUAGE_VERSION));
    glEnable( GL_DEBUG_OUTPUT );
    glDebugMessageCallback( MessageCallback, 0 );
    return true;
}

void Window::update() {
    SDL_GL_SwapWindow(window);
    pollEvents();
}

void Window::cleanup() {
    SDL_DestroyWindow(window);
}

bool Window::isRunning() const {
    return running;
}

void Window::setVsync(const bool &vsync) {
    if(!SDL_GL_SetSwapInterval(vsync)) {
        fprintf(stderr, "Vsync failed, not supported\n");
    }
}

void Window::pollEvents() {
    input->resetPressed();
    SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            input->pressKey(event.key.keysym.scancode);
            break;
        case SDL_KEYUP:
            input->releaseKey(event.key.keysym.scancode);
            break;
        default:
            break;
        }
	}
}

SDL_Window* Window::getWindow() {
    return window;
}

std::string Window::getTitle() const {
    return title;
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
