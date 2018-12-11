#include "FboFactory.h"

namespace Factory {

    FboFactory* FBO = nullptr;

    FboFactory::FboFactory() { FBO = this; }

    FboFactory::~FboFactory() {
        for(auto fbo : fbos)
            fbo.second->remove();
        fbos.clear();
    }

    void FboFactory::removeFbo(const std::string &id) {
        if(isLoaded(id))
            fbos.erase(id);
    }

    bool FboFactory::isLoaded(const std::string &source) const {
        return (fbos.find(source) != fbos.end());
    }

}
