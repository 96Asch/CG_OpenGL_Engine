#include "ShadowFbo.h"

ShadowFbo::ShadowFbo() {

}

ShadowFbo::~ShadowFbo() {
    remove();
}

bool ShadowFbo::init(const unsigned int &width, const unsigned int &height) {
    glGenFramebuffers(1, &id);

    glGenTextures(1, &shadowMap);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height,
                 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                            GL_TEXTURE_2D, shadowMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    GLenum stat = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (stat != GL_FRAMEBUFFER_COMPLETE) {
        printf("FB error, stat: 0x%x\n", stat);
        return false;
    }
    return true;
}

void ShadowFbo::remove() {
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(1, &shadowMap);
}

void ShadowFbo::bindForWriting() {
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, id);
}

void ShadowFbo::bindForReading(GLenum texUnit) {
    glActiveTexture(texUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
    this->texUnit = texUnit;
}

void ShadowFbo::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowFbo::unbindTexture() {
    glActiveTexture(this->texUnit);
    glBindTexture(GL_TEXTURE_2D, shadowMap);
}
