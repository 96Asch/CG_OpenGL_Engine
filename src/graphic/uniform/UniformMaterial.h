#ifndef UNIFORMMATERIAL_H_
#define UNIFORMMATERIAL_H_

#include "Uniform.h"
#include "UniformVec4.h"
#include "../../component/Material.h"

struct UniformMaterial : public Uniform {


    UniformMaterial(const std::string &name)
                    : Uniform(name),
                      diffuse(UniformVec4(name + ".diffuse")),
                      specularPower(UniformFloat(name + ".specularPower")),
                      hasTexture(UniformFloat(name + ".hasTexture")),
                      reflectance(UniformFloat(name + ".reflectance"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        diffuse.storeUniformLocation(id);
        specularPower.storeUniformLocation(id);
        hasTexture.storeUniformLocation(id);
        reflectance.storeUniformLocation(id);
    };

    void load(const Material &mat) {
        diffuse.load(mat.diffuse);
        specularPower.load(mat.specularPower);
        hasTexture.load(mat.hasTexture);
        reflectance.load(mat.reflectance);
    };

    UniformVec4 diffuse;
    UniformFloat specularPower;
    UniformFloat hasTexture;
    UniformFloat reflectance;

};

#endif
