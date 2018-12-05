#ifndef UNIFORMSAMPLERS_H_
#define UNIFORMSAMPLERS_H_

#include <memory>
#include <vector>

#include "Uniform.h"

#define MAX_SAMPLERS 5

struct UniformSamplers : public Uniform {

    UniformSamplers(const std::string &name)
                    : Uniform(name)
    {
        samplers.resize(MAX_SAMPLERS);
        for(unsigned i = 0; i < MAX_SAMPLERS; ++i)
            samplers[i].reset(new UniformSampler(name + "[" + std::to_string(i) + "]"));
    };

    virtual void storeUniformLocation(const GLuint &id) override {
        for(auto &sampler : samplers)
            sampler->storeUniformLocation(id);
    };

    void loadTexUnits(const unsigned &unitStart) {
        for(unsigned i = unitStart; i < unitStart + MAX_SAMPLERS; ++i) {
            samplers[i - unitStart]->loadTexUnit(i);
        }
    };

    std::vector<std::unique_ptr<UniformSampler>> samplers;
};


#endif
