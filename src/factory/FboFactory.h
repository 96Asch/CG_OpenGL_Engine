#ifndef FBOLOADER_H_
#define FBOLOADER_H_

#include <map>
#include <memory>
#include <string>

#include "../graphic/globjects/Fbo.h"

namespace Factory {

    class FboFactory;

    extern FboFactory* FBO;

    class FboFactory {

    public:

        FboFactory();

        ~FboFactory();

        void createFbo(const std::string &id,
                       const unsigned &colorUnit,
                       const unsigned &width,
                       const unsigned &height);

        void removeFbo(const std::string &id);

        std::shared_ptr<Fbo> getFbo(const std::string &id);

        bool isLoaded(const std::string &id) const;

    private:

        std::map<std::string, std::shared_ptr<Fbo>> fbos;

    };

};

#endif
