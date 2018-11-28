#ifndef UNIFORMMATERIAL_H_
#define UNIFORMMATERIAL_H_

#include "Uniform.h"
#include "UniformVec4.h"
#include "../../component/Material.h"

struct UniformMaterial : public Uniform {


    UniformMaterial(const std::string &name)
                    : Uniform(name),
                      ambient(UniformVec4(name + ".ambient")),
                      diffuse(UniformVec4(name + ".diffuse")),
                      specular(UniformVec4(name + ".specular")),
                      hasTexture(UniformFloat(name + ".hasTexture")),
                      reflectance(UniformFloat(name + ".reflectance")),
                      hasFakeLighting(UniformFloat(name + ".hasFakeLighting")),
                      hasNormalMap(UniformFloat(name + ".hasNormalMap"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        ambient.storeUniformLocation(id);
        diffuse.storeUniformLocation(id);
        specular.storeUniformLocation(id);
        hasTexture.storeUniformLocation(id);
        reflectance.storeUniformLocation(id);
        hasFakeLighting.storeUniformLocation(id);
        hasNormalMap.storeUniformLocation(id);
    };

    void load(const Material &mat) {
        ambient.load(mat.ambient);
        diffuse.load(mat.diffuse);
        specular.load(mat.specular);
        hasTexture.load(mat.hasTexture);
        reflectance.load(mat.reflectance);
        hasFakeLighting.load(mat.hasFakeLighting);
        hasNormalMap.load(mat.hasNormalMap);
    };

    UniformVec4 ambient;
    UniformVec4 diffuse;
    UniformVec4 specular;
    UniformFloat hasTexture;
    UniformFloat reflectance;
    UniformFloat hasFakeLighting;
    UniformFloat hasNormalMap;

};

#endif
