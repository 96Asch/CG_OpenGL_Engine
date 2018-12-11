#ifndef UNIFORMSLIGHTS_H_
#define UNIFORMSLIGHTS_H_

#include <vector>
#include <memory>

#include "Uniform.h"
#include "UniformSLight.h"
#include "Global.h"
#include "../../component/SpotLight.h"


struct UniformSLights : public Uniform {

    UniformSLights(const std::string &name)
                    : Uniform(name)
    {
        lights.resize(Global::MAX_SPOT_LIGHTS);
        for(unsigned i = 0; i < Global::MAX_SPOT_LIGHTS; i++)
            lights[i].reset(new UniformSLight(name + "[" + std::to_string(i) + "]"));
    }

    virtual void storeUniformLocation(const GLuint &id) override {
        for(unsigned i = 0; i < Global::MAX_SPOT_LIGHTS; i++)
            lights[i]->storeUniformLocation(id);
    }

    void load(const SpotLight &sLight,
              const glm::vec3 &pos,
              const glm::vec3 &dir,
              const unsigned &i)
    {
        if(i < Global::MAX_SPOT_LIGHTS)
            lights[i]->load(sLight, pos, dir);
        else
            lights[i]->load(SpotLight(), glm::vec3(0.0f), glm::vec3(0.0f));
    }

    void loadEmpty(const unsigned &index) {
        if(index < Global::MAX_SPOT_LIGHTS)
            lights[index]->load(SpotLight(), glm::vec3(0.0f),  glm::vec3(0.0f));
    }


    std::vector<std::unique_ptr<UniformSLight>> lights;
};

#endif
