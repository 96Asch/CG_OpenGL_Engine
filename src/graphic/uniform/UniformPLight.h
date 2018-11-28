#ifndef UNIFORMPLIGHT_H_
#define UNIFORMPLIGHT_H_

#include "Uniform.h"
#include "UniformVec3.h"
#include "UniformFloat.h"
#include "../../component/PointLight.h"

struct UniformPLight : public Uniform {

    UniformPLight(const std::string &name)
                  : Uniform(name),
                    color(UniformVec3(name + ".color")),
                    position(UniformVec3(name + ".position")),
                    intensity(UniformFloat(name + ".intensity")),
                    attenuation(UniformVec3(name + ".attenuation"))
                    {};

    virtual void storeUniformLocation(const GLuint &id) override {
        color.storeUniformLocation(id);
        position.storeUniformLocation(id);
        intensity.storeUniformLocation(id);
        attenuation.storeUniformLocation(id);
    }

    void load(const PointLight &light) {
        color.load(light.color);
        position.load(light.position);
        intensity.load(light.intensity);
        attenuation.load(light.attenuation);
    };

    UniformVec3 color;
    UniformVec3 position;
    UniformFloat intensity;
    UniformVec3 attenuation;
};

#endif
