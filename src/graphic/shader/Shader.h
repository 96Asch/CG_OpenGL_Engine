#ifndef Shader_H_
#define Shader_H_

#include <string>
#include <initializer_list>
#include <iostream>
#include <unordered_map>
#include "../uniform/Uniform.h"
#include "Global.h"

class Shader {

public:

    Shader();

    ~Shader();

    void init(const std::string &vs,
              const std::string &fs,
              std::initializer_list<std::string> &&attribs);

    void init(const std::string &vs,
              const std::string &fs,
              const std::string &gs,
              std::initializer_list<std::string> &&attribs);

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

    void bindAttributes(std::initializer_list<std::string> &&attribs);

    GLuint loadShader(const std::string &file, const GLenum &type);


};

template <typename T>
T* Shader::getUniform(const std::string &name) {
    auto search = uniforms.find(name);
    if(search != uniforms.end())
        return static_cast<T*>(search->second);
    throw std::runtime_error("Could not find uniform: " + name + " in the shader");
    return nullptr;
}

#endif
