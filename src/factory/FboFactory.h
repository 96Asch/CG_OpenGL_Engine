#ifndef FBOFACTORY_H_
#define FBOFACTORY_H_

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "../graphic/globjects/Fbo.h"

namespace Factory {

    class FboFactory;

    extern FboFactory* FBO;

    class FboFactory {

    public:

        FboFactory();

        ~FboFactory();

        template <typename T, typename... Args>
        std::shared_ptr<Fbo> createFbo(const std::string &id, Args... args);

        void removeFbo(const std::string &id);

        template <typename T>
        std::shared_ptr<T> getFbo(const std::string &source);

        bool isLoaded(const std::string &source) const;

    private:

        std::map<std::string, std::shared_ptr<Fbo>> fbos;

    };

    template <typename T, typename... Args>
    std::shared_ptr<Fbo> FboFactory::createFbo(const std::string &id,
                                               Args... args)
    {
        if(!isLoaded(id))
            fbos.insert({id, std::make_shared<T>(args...)});
        return fbos[id];
    };

    template <typename T>
    std::shared_ptr<T> FboFactory::getFbo(const std::string &source) {
        if(isLoaded(source))
            return std::static_pointer_cast<T>(fbos[source]);
        throw std::runtime_error("Error: cannot find FBO for: " + source);
        return nullptr;
    }


};

#endif
