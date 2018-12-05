#include "Shader.h"

Shader::Shader() = default;

Shader::~Shader() {
    for(auto pair : uniforms)
        delete pair.second;
    uniforms.clear();
}

void Shader::init(const std::string &vs,
                  const std::string &fs,
                  std::initializer_list<std::string> &&attribs)
{
    init(vs, fs, "", std::move(attribs));
}

void Shader::init(const std::string &vs,
                  const std::string &fs,
                  const std::string &gs,
                  std::initializer_list<std::string> &&attribs)
{
    GLuint vsId = loadShader(vs, GL_VERTEX_SHADER),
           fsId = loadShader(fs, GL_FRAGMENT_SHADER),
           gsId;
    if(!gs.empty())
        gsId = loadShader(gs, GL_GEOMETRY_SHADER);

    int isLinked, maxLength;
    char* infolog;
    id = glCreateProgram();
    glAttachShader(id, vsId);
    glAttachShader(id, fsId);
    if(!gs.empty())
        glAttachShader(id, gsId);
    bindAttributes(std::move(attribs));
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
    if(!gs.empty()) {
        glDetachShader(id, gsId);
        glDeleteShader(gsId);
    }
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

void Shader::addUniform(Uniform *uniform) {
    uniforms.insert({uniform->name, uniform});
}

void Shader::storeUniformLocations() {
    for(auto pair : uniforms)
        pair.second->storeUniformLocation(id);
    glValidateProgram(id);
}


void Shader::bindAttributes(std::initializer_list<std::string> &&attribs) {
    GLuint location = 0;
    for(auto a : attribs) {
        glBindAttribLocation(id, location, a.c_str());
        ++location;
    }
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
         throw std::runtime_error("Could not compile shaders");
    }
    return shaderId;
}
