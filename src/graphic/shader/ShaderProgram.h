#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#include <string>
#include "Uniform.h"
#include "Global.h"

class Uniform;
struct ShaderAttribute;
class ShaderProgram {

public:

    ShaderProgram(const std::string &vsFile,
                  const std::string &fsFile,
                  const std::string &var...);

    ShaderProgram(const std::string &vsFile,
                   const std::string &fsFile,
                   const ShaderAttribute &attribs...);

    ~ShaderProgram();

    void start();

    void stop();

    void cleanup();

private:

    GLuint id;
    GLchar *vs, *fs;

    void bindAttributes(int location, const std::string &attrib) {
        glBindAttribLocation(id, location, attrib.c_str());
    }

    template <typename... Args>
    void bindAttributes(int location, const std::string &first, Args... args) {
        glBindAttribLocation(id, location, first.c_str());
        ++location;
        bindAttributes(location, args...);
    }

    GLuint loadShader(const std::string &file, GLchar* &shader, const GLenum &type);


protected:


    void storeUniformLocations(Uniform uniform) {
        uniform.storeUniformLocation(id);
    }

    template <typename... Args>
    void storeUniformLocations(Uniform uniform, Args... args) {
        uniform.storeUniformLocation(id);
        storeUniformLocations(args...);
    }

};

#endif
