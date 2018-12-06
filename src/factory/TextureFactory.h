#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "Global.h"

struct Texture;

namespace Factory {

    class TextureFactory;
    extern TextureFactory* TEXTURE;

    class TextureFactory {

    public:

        TextureFactory();

        ~TextureFactory();

        GLuint createTexture(const std::string &file);

        GLuint createCubeMapTexture(const std::vector<std::string> &files);

        GLuint getTexture(const std::string &file);

        bool isLoaded(const std::string &id);

        void removeTexture(const std::string &file);

    private:

        std::unordered_map<std::string, GLuint> textures;

        bool loadCubeMapSide(GLuint texture, GLenum side_target,
                             const std::string file);

    };
}

#endif
