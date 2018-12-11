#ifndef UNIFORMBASELIGHT_H_
#define UNIFORMBASELIGHT_H_

#include "Uniform.h"

#include "../../environment/BaseLight.h"

struct UniformBaseLight : public Uniform {

    UniformBaseLight(const std::string &name) : Uniform(name),
                                                color(UniformVec3(name + ".color")),
                                                intensity(UniformFloat(name + ".intensity"))
                                                {};


    virtual void storeUniformLocation(const GLuint &id) override {
        color.storeUniformLocation(id);
        intensity.storeUniformLocation(id);
    }

    void load(const BaseLight &light) {
        color.load(light.color);
        intensity.load(light.intensity);
    }

    UniformVec3 color;
    UniformFloat intensity;

};

#endif
