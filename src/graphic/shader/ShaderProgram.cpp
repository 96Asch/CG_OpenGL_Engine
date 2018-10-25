#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() = default;

ShaderProgram::~ShaderProgram() {
    if(vs)
        delete[] vs;
    if(fs)
        delete[] fs;
}

void ShaderProgram::init(const std::string &shader,
                         const std::string &attribs...) {
    GLuint vsId = loadShader(shader + ".vs", vs, GL_VERTEX_SHADER),
           fsId = loadShader(shader + ".fs", fs, GL_FRAGMENT_SHADER);
    int isLinked, maxLength;
    char* infolog;

    id = glCreateProgram();
    glAttachShader(id, vsId);
    glAttachShader(id, fsId);
    bindAttributes<std::string>(0, attribs);
    glLinkProgram(id);

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


void ShaderProgram::start() {
    glUseProgram(id);
}

void ShaderProgram::stop() {
    glUseProgram(0);
}

void ShaderProgram::cleanup() {
    stop();
    glDeleteProgram(id);
}

GLuint ShaderProgram::loadShader(const std::string &file, GLchar* &shader, const GLenum &type) {
    int isCompiled, maxLength;
    char* infolog;

    shader = Util::resourceToChar(Global::resources + file);
    GLuint shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, (const GLchar**)&shader, 0);
    glCompileShader(shaderId);
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &isCompiled);
    if(isCompiled == GL_FALSE) {
         glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &maxLength);
         infolog = new char[maxLength];
         glGetShaderInfoLog(shaderId, maxLength, &maxLength, infolog);
         fprintf(stderr, "%s\n", infolog);
         delete[] infolog;
         exit(0);
    }
    return shaderId;
}
