#include "Uniform.h"

Uniform::Uniform(const std::string &name) : name(name) {}

Uniform::~Uniform(){}

void Uniform::storeUniformLocation(const GLuint &id) {
    location = glGetUniformLocation(id, name.c_str());
    if(location == -1)
        fprintf(stderr, "Could not find: %s\n", name.c_str());
}

GLint Uniform::getLocation() const {
    return location;
}
