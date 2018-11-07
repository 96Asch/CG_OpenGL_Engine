#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>

#include "TextureFactory.h"

namespace Factory {

    TextureFactory* TEXTURE = nullptr;

    const float bias = -0.04f;

    TextureFactory::TextureFactory() { TEXTURE = this; }

    TextureFactory::~TextureFactory() {
        for(auto pair : textures)
            glDeleteTextures(1, &pair.second);
    }

    GLuint TextureFactory::createTexture(const std::string &file) {
        auto it = textures.find(file);
        if(it != textures.end())
            return it->second;

        int w, h, components;
        GLuint id;
        unsigned char* image = stbi_load((Global::resources + file).c_str(),
                                          &w, &h, &components, STBI_rgb_alpha);
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D,
                        GL_TEXTURE_MIN_FILTER,
                        GL_LINEAR_MIPMAP_LINEAR);

        glTexParameterf(GL_TEXTURE_2D,
                        GL_TEXTURE_LOD_BIAS,
                        bias);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w,
                     h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(image);
        textures.insert({file, id});
        return id;
    }

    void TextureFactory::removeTexture(const std::string &file) {
        auto it = textures.find(file);
        GLuint texture;
        if(it != textures.end()) {
            texture = it->second;
            textures.erase(it);
            glDeleteTextures(1, &texture);
        }
    }
}
