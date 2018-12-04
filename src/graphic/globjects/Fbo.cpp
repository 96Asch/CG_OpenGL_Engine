#include "Fbo.h"
#include "Global.h"

Fbo::Fbo(const GLuint &id,
         const unsigned &colorUnit,
         const unsigned &width,
         const unsigned &height)
         :id(id)
{
    initTexture(colorUnit, width, height);
    initDepthTexture(width, height);
    initDepthBuffer(width, height);
}

Fbo::~Fbo() {
    remove();
}

std::shared_ptr<Fbo> Fbo::create(const unsigned &colorUnit,
                                 const unsigned &width,
                                 const unsigned &height)
{
    GLuint id;
    glGenFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + colorUnit);
    return std::make_shared<Fbo>(id, colorUnit, width, height);
}

void Fbo::bind(const unsigned &width, const unsigned &height) {
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glViewport(0, 0, width, height);
}

void Fbo::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, Global::width, Global::height);
}

void Fbo::remove() {
    glDeleteFramebuffers(1, &id);
    glDeleteRenderbuffers(1, &depthBuffer);
    glDeleteTextures(1, &depthTexture);
    glDeleteTextures(1, &colorTexture);
}

GLuint Fbo::getColorTexture() {
    return colorTexture;
}

GLuint Fbo::getDepthTexture() {
    return depthTexture;
}

void Fbo::initTexture(const unsigned &colorUnit,
                      const unsigned &width,
                      const unsigned &height)
{
    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorUnit, colorTexture, 0);
}

void Fbo::initDepthTexture(const unsigned &width,
                           const unsigned &height)
{
    glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);
}

void Fbo::initDepthBuffer(const unsigned &width,
                          const unsigned &height)
{
    glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, depthBuffer);
}
