#ifndef UNIFORM_H_
#define UNIFORM_H_

#include <string>
#include "Global.h"

class Uniform {

public:

    Uniform(const std::string &name);

    virtual ~Uniform();

    void storeUniformLocation(const GLuint &id);

    GLint getLocation() const;

private:

    std::string name;

    GLint location;
};

#endif
