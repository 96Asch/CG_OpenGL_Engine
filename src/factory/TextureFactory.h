#ifndef TEXTUREFACTORY_H_
#define TEXTUREFACTORY_H_

#include <string>
#include <unordered_map>

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
        void removeTexture(const std::string &file);


    private:
        std::unordered_map<std::string, GLuint> textures;

    };
}

#endif