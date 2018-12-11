#ifndef UNIFORMDLIGHT_H_
#define UNIFORMDLIGHT_H_

#include "Uniform.h"
#include "UniformVec3.h"
#include "UniformBaseLight.h"
#include "../../environment/DirectionalLight.h"

struct UniformDLight : public Uniform {

    UniformDLight(const std::string &name)
                    : Uniform(name),
                      light(UniformBaseLight(name + ".light")),
                      direction(UniformVec3(name + ".direction"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        light.storeUniformLocation(id);
        direction.storeUniformLocation(id);
    }

    void load(const DirectionalLight &dLight) {
        light.load(dLight.light);
        direction.load(dLight.direction);
    }

    UniformBaseLight light;
    UniformVec3 direction;
};

#endif
