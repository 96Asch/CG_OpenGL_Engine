#ifndef UNIFORMDLIGHT_H_
#define UNIFORMDLIGHT_H_

#include "Uniform.h"
#include "UniformVec3.h"
#include "UniformFloat.h"
#include "../../environment/DirectionalLight.h"

struct UniformDLight : public Uniform {

    UniformDLight(const std::string &name)
                    : Uniform(name),
                      color(UniformVec3(name + ".color")),
                      direction(UniformVec3(name + ".direction")),
                      intensity(UniformFloat(name + ".intensity"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        color.storeUniformLocation(id);
        direction.storeUniformLocation(id);
        intensity.storeUniformLocation(id);
    }

    void load(const DirectionalLight &light) {
        color.load(light.color);
        direction.load(light.direction);
        intensity.load(light.intensity);
    }

    UniformVec3 color;
    UniformVec3 direction;
    UniformFloat intensity;
};

#endif
