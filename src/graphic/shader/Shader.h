#ifndef Shader_H_
#define Shader_H_

#include <string>
#include <unordered_map>
#include "../uniform/Uniform.h"
#include "Global.h"

class Shader {

public:

    Shader();

    ~Shader();

    template <typename... Args>
    void init(const std::string &shader,
              const Args... attribs);

    void start();

    void stop();

    void cleanup();

    void addUniform(const std::string &name, Uniform* uniform);

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
void Shader::init(const std::string &shader,
                         const Args... attribs) {
    GLuint vsId = loadShader(shader + ".vs", GL_VERTEX_SHADER),
           fsId = loadShader(shader + ".fs", GL_FRAGMENT_SHADER);
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
        fprintf(stderr, "Error: %s\n", infolog);
        exit(0);
    }

    glDetachShader(id, vsId);
    glDetachShader(id, fsId);
    glDeleteShader(vsId);
    glDeleteShader(fsId);
}

template <typename T>
T* Shader::getUniform(const std::string &name) {
    auto search = uniforms.find(name);
    if(search != uniforms.end())
        return (T*) search->second;
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
