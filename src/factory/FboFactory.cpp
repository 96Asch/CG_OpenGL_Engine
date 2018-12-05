#include "FboFactory.h"

namespace Factory {

    FboFactory* FBO = nullptr;

    FboFactory::FboFactory() { FBO = this; }

    FboFactory::~FboFactory() {
        fbos.clear();
    }

    std::shared_ptr<Fbo> FboFactory::getFbo(const std::string &source) {
        if(isLoaded(source))
            return fbos[source];
        throw std::runtime_error("Error: cannot find FBO for: " + source);
        return nullptr;
    }

    void FboFactory::removeFbo(const std::string &id) {
        if(isLoaded(id))
            fbos.erase(id);
    }

    bool FboFactory::isLoaded(const std::string &source) const {
        return (fbos.find(source) != fbos.end());
    }

}
