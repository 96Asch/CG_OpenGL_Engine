#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <string>
#include "Global.h"

class Uniform {

private:

    std::string name;
    GLint location;

protected:
    Uniform(const std::string &name);

    virtual ~Uniform();

    void storeUniformLocation(const GLuint &id);

    GLint getLocation() const;

friend class ShaderProgram;
};

#endif
