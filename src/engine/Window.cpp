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

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
  	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

    SDL_WM_SetCaption(title.c_str(), 0);
    window = SDL_SetVideoMode(width, height, 32,
                              SDL_OPENGL | SDL_DOUBLEBUF);
    if(!window) {
        fprintf(stderr, "SDL failed to initialize");
        return false;
    }

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
    return true;
}

void Window::update() {
    SDL_GL_SwapBuffers();
    pollEvents();
}

void Window::cleanup() {
    SDL_FreeSurface(window);
}

bool Window::isRunning() const {
    return running;
}

void Window::setVsync(const bool &vsync) {
    // SDL_GL_SetSwapInterval(vsync);
}

void Window::pollEvents() {
    SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
        case SDL_QUIT:
            running = false;
            break;
        case SDL_KEYDOWN:
            input->pressKey(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            input->releaseKey(event.key.keysym.sym);
            break;
        default:
            break;
        }
	}
}

SDL_Surface* Window::getWindow() {
    return window;
}

std::string Window::getTitle() const {
    return title;
}

void Window::setTitle(const std::string &newTitle) {
    SDL_WM_SetCaption(newTitle.c_str(), 0);
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
