#ifndef UNIFORMPLIGHTS_H_
#define UNIFORMPLIGHTS_H_

#include <vector>
#include <memory>

#include "Uniform.h"
#include "UniformPLight.h"
#include "Global.h"
#include "../../component/PointLight.h"


struct UniformPLights : public Uniform {

    UniformPLights(const std::string &name)
                    : Uniform(name)
    {
        lights.resize(Global::MAX_POINT_LIGHTS);
        for(unsigned i = 0; i < Global::MAX_POINT_LIGHTS; i++)
            lights[i].reset(new UniformPLight(name + "[" + std::to_string(i) + "]"));
    }

    virtual void storeUniformLocation(const GLuint &id) override {
        for(unsigned i = 0; i < Global::MAX_POINT_LIGHTS; i++)
            lights[i]->storeUniformLocation(id);
    }

    void load(const std::vector<PointLight> &pLights) {
        for(unsigned i = 0; i < Global::MAX_POINT_LIGHTS; ++i) {
            if(i < pLights.size())
                lights[i]->load(pLights[i]);
            else
                lights[i]->load(PointLight());
        }
    }

    std::vector<std::unique_ptr<UniformPLight>> lights;
};

#endif
