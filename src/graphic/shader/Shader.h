#ifndef Shader_H_
#define Shader_H_

#include <string>
#include <iostream>
#include <unordered_map>
#include "../uniform/Uniform.h"
#include "Global.h"

class Shader {

public:

    Shader();

    ~Shader();

    template <typename... Args>
    void init(const std::string &vert,
              const std::string &frag,
              const Args... attribs);

    template <typename... Args>
    void init(const std::string &shader,
              const Args... attribs);

    void start();

    void stop();

    void cleanup();

    void addUniform(Uniform* uniform);

    template <typename T>
    T* getUniform(const std::string &name);

    void storeUniformLocations();

private:

    GLuint id;
    std::unordered_map<std::string, Uniform*> uniforms;

    template <typename... Args>
    void bindAttributes(Args... args);

    GLuint loadShader(const std::string &file, const GLenum &type);


};

template <typename... Args>
void Shader::init(const std::string &vert,
                  const std::string &frag,
                  const Args... attribs)
{
    GLuint vsId = loadShader(vert, GL_VERTEX_SHADER),
           fsId = loadShader(frag, GL_FRAGMENT_SHADER);
    int isLinked, maxLength;
    char* infolog;
    id = glCreateProgram();
    glAttachShader(id, vsId);
    glAttachShader(id, fsId);
    bindAttributes<std::string>(attribs...);
    glLinkProgram(id);
    glValidateProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE) {
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
        infolog = new char[maxLength];
        glGetProgramInfoLog(id, maxLength, &maxLength, infolog);
        std::cerr << "SHADER LINK ERROR: " << infolog << std::endl;
        delete[] infolog;
        throw std::runtime_error("Could not link shaders");
    }

    glDetachShader(id, vsId);
    glDetachShader(id, fsId);
    glDeleteShader(vsId);
    glDeleteShader(fsId);
}

template <typename... Args>
void Shader::init(const std::string &shader,
                  const Args... attribs)
{
    init(shader + ".vs", shader + ".fs", attribs...);
}

template <typename T>
T* Shader::getUniform(const std::string &name) {
    auto search = uniforms.find(name);
    if(search != uniforms.end())
        return static_cast<T*>(search->second);
    throw std::runtime_error("Could not find uniform: " + name + " in the shader");
    return nullptr;
}

template <typename... Args>
void Shader::bindAttributes(Args... args) {
    GLuint location = 0;
    Util::pack_foreach([this, &location](const std::string &attrib){
        glBindAttribLocation(id, location, attrib.c_str());
        ++location;
    }, args...);
}

#endif
