#ifndef UNIFORMPLIGHT_H_
#define UNIFORMPLIGHT_H_

#include "Uniform.h"
#include "UniformVec3.h"
#include "UniformBaseLight.h"
#include "../../component/PointLight.h"

struct UniformPLight : public Uniform {

    UniformPLight(const std::string &name)
                  : Uniform(name),
                    light(UniformBaseLight(name + ".light")),
                    position(UniformVec3(name + ".position")),
                    attenuation(UniformVec3(name + ".attenuation"))
                    {};

    virtual void storeUniformLocation(const GLuint &id) override {
        light.storeUniformLocation(id);
        position.storeUniformLocation(id);
        attenuation.storeUniformLocation(id);
    }

    void load(const PointLight &pLight) {
        light.load(pLight.light);
        position.load(pLight.position);
        attenuation.load(pLight.attenuation);
    };

    UniformBaseLight light;
    UniformVec3 position;
    UniformVec3 attenuation;
};

#endif
