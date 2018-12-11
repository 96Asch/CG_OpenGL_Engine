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

    void load(const PointLight &pLight, const glm::vec3 &pos, const unsigned &i) {
        if(i < Global::MAX_POINT_LIGHTS)
            lights[i]->load(pLight, pos);
        else
            lights[i]->load(PointLight(), glm::vec3(0.0f));
    }

    void loadEmpty(const unsigned &index) {
        if(index < Global::MAX_POINT_LIGHTS)
            lights[index]->load(PointLight(), glm::vec3(0.0f));
    }

    std::vector<std::unique_ptr<UniformPLight>> lights;
};

#endif
