#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_
#include <string>
#include "Global.h"

class Uniform;
struct ShaderAttribute;
class ShaderProgram {

public:

    ShaderProgram(const std::string &vs,
                  const std::string &fs,
                  const std::string &var...);

    ShaderProgram (const std::string &vs,
                   const std::string &fs,
                   const ShaderAttribute &attribs...);

    void start();

    void stop();

    void cleanup();

private:

    void bindAttributes(const std::string &attribs...);

    void bindAttributes(const ShaderAttribute &attribs...);

    GLuint loadShader(const std::string &file, GLenum type);


protected:

    void storeUniformLocations(Uniform uniforms...);

};

#endif
