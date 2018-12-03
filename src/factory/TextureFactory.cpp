#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <iostream>

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
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

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

    GLuint TextureFactory::createCubeMapTexture(const std::vector<std::string> &files) {
        auto it = textures.find(files.front());
        if(it != textures.end())
            return it->second;

        GLuint id;

        glGenTextures(1, &id);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        for(unsigned i = 0; i < files.size(); ++i) {
            loadCubeMapSide(id, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                            Global::resources + files.at(i));
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        textures.insert({files.front(), id});
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

    bool TextureFactory::loadCubeMapSide(GLuint texture, GLenum side_target,
                                         const std::string file)
    {
      glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

      int w, h, components;
      int force_channels = 4;
      unsigned char* image = stbi_load(file.c_str(), &w, &h, &components,
                                       force_channels);
      if (!image) {
        fprintf(stderr, "ERROR: could not load %s\n", file.c_str());
        return false;
      }

      if ((w & (w - 1)) != 0 || (h & (h - 1)) != 0) {
        fprintf(stderr,
        	"WARNING: image %s is not power-of-2 dimensions\n",
        	file.c_str());
      }

      glTexImage2D(side_target, 0, GL_RGBA, w, h,
                    0, GL_RGBA, GL_UNSIGNED_BYTE, image);
      stbi_image_free(image);
      return true;
    }
}
