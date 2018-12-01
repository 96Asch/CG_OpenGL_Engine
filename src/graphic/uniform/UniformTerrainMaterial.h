#ifndef UNIFORMTERRAINMATERIAL_H_
#define UNIFORMTERRAINMATERIAL_H_

#include "Uniform.h"
#include "UniformVec4.h"
#include "../../component/Material.h"

struct UniformTerrainMaterial : public Uniform {


    UniformTerrainMaterial(const std::string &name)
                    : Uniform(name),
                      ambient(UniformVec4(name + ".ambient")),
                      diffuse(UniformVec4(name + ".diffuse")),
                      specular(UniformVec4(name + ".specular")),
                      hasTexture(UniformFloat(name + ".hasTexture")),
                      reflectance(UniformFloat(name + ".reflectance"))
                      {};

    virtual void storeUniformLocation(const GLuint &id) override {
        ambient.storeUniformLocation(id);
        diffuse.storeUniformLocation(id);
        specular.storeUniformLocation(id);
        hasTexture.storeUniformLocation(id);
        reflectance.storeUniformLocation(id);
    };

    void load(const Material &mat) {
        ambient.load(mat.ambient);
        diffuse.load(mat.diffuse);
        specular.load(mat.specular);
        hasTexture.load(mat.hasTexture);
        reflectance.load(mat.reflectance);
    };

    UniformVec4 ambient;
    UniformVec4 diffuse;
    UniformVec4 specular;
    UniformFloat hasTexture;
    UniformFloat reflectance;

};

#endif
