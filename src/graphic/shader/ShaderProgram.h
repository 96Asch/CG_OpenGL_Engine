#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#include <string>
#include "../uniform/Uniform.h"
#include "Global.h"

class ShaderProgram {

public:

    ShaderProgram();

    ~ShaderProgram();

    void init(const std::string &shader,
              const std::string &var...);

    void start();

    void stop();

    void cleanup();

private:

    GLuint id;
    GLchar *vs, *fs;

    template <typename... Args>
    void bindAttributes(Args... args);

    GLuint loadShader(const std::string &file, GLchar* &shader, const GLenum &type);


protected:

    template <typename... Args>
    void storeUniformLocations(Args... args);

};

template <typename... Args>
void ShaderProgram::bindAttributes(Args... args) {
    GLuint location = 0;
    Util::pack_foreach([this, &location](const std::string &attrib){
        glBindAttribLocation(id, location, attrib.c_str());
        printf("SHADER BIND AT: %i",location);
        ++location;
    }, args...);
}

template <typename... Args>
void ShaderProgram::storeUniformLocations(Args... args) {
    Util::pack_foreach([this](Uniform* uniform) {
        uniform->storeUniformLocation(id);
    }, args...);
    glValidateProgram(id);
}

#endif
