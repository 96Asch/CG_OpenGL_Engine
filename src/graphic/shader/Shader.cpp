#include "Shader.h"

Shader::Shader() = default;

Shader::~Shader() {
    for(auto pair : uniforms)
        delete pair.second;
    uniforms.clear();
}


void Shader::start() {
    glUseProgram(id);
}

void Shader::stop() {
    glUseProgram(0);
}

void Shader::cleanup() {
    stop();
    glDeleteProgram(id);
}

void Shader::addUniform(const std::string &name, Uniform *uniform) {
    uniforms.insert({name, uniform});
}

void Shader::storeUniformLocations() {
    for(auto pair : uniforms)
        pair.second->storeUniformLocation(id);
    glValidateProgram(id);
}

GLuint Shader::loadShader(const std::string &file, const GLenum &type) {
    int isCompiled, maxLength;
    char* infolog;
    std::string shaderString = Util::resourceToString(Global::resources + file);
    const GLchar* shader = shaderString.c_str();
    GLuint shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &shader, nullptr);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
         glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
         infolog = new char[maxLength];
         glGetShaderInfoLog(shaderId, maxLength, &maxLength, infolog);
         fprintf(stderr, "SHADER ERROR: %s\n", infolog);
         delete[] infolog;
         exit(-1);
    }
    return shaderId;
}
