#ifndef UNIFORMSPECULAR_H_
#define UNIFORMSPECULAR_H_

#include "Uniform.h"
#include "UniformFloat.h"

struct UniformSpecular : public Uniform {


    UniformSpecular(const std::string &name)
                    : Uniform(name),
                      specularPower(UniformFloat(name + ".specularPower")),
                      reflectance(UniformFloat(name + ".reflectance"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        specularPower.storeUniformLocation(id);
        reflectance.storeUniformLocation(id);
    };

    void load(const float &power, const float &reflect) {
        specularPower.load(power);
        reflectance.load(reflect);
    };

    UniformFloat specularPower;
    UniformFloat reflectance;
};

#endif
