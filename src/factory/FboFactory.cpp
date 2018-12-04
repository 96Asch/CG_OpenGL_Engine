#include "FboFactory.h"


namespace Factory {

    FboFactory* FBO = nullptr;

    FboFactory::FboFactory() {
        FBO = this;
    }

    FboFactory::~FboFactory() {
        fbos.clear();
    }

    void FboFactory::createFbo(const std::string &id,
                               const unsigned &colorUnit,
                               const unsigned &width,
                               const unsigned &height)
    {
        if(!isLoaded(id)) {
            auto fbo = Fbo::create(colorUnit, width, height);
            fbo->unbind();
            fbos[id] = std::move(fbo);
        }
    }

    void FboFactory::removeFbo(const std::string &id) {
        fbos.erase(id);
    }

    std::shared_ptr<Fbo> FboFactory::getFbo(const std::string &id) {
        return fbos[id];
    }

    bool FboFactory::isLoaded(const std::string &id) const {
        return (fbos.find(id) != fbos.end());
    }

}
