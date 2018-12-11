#ifndef UNIFORMFOG_H_
#define UNIFORMFOG_H_

#include "Uniform.h"
#include "../../environment/Fog.h"

struct UniformFog : public Uniform {


    UniformFog(const std::string &name)
                : Uniform(name),
                  fogActive(UniformFloat(name + ".isActive")),
                  color(UniformVec3(name + ".color")),
                  density(UniformFloat(name + ".density")),
                  gradient(UniformFloat(name + ".gradient"))
    {};

    virtual void storeUniformLocation(const GLuint &id) override {
        fogActive.storeUniformLocation(id);
        color.storeUniformLocation(id);
        density.storeUniformLocation(id);
        gradient.storeUniformLocation(id);
    }

    void load(const Fog &fog) {
        fogActive.load(fog.active);
        color.load(fog.color);
        density.load(fog.density);
        gradient.load(fog.gradient);
    };

    UniformFloat fogActive;
    UniformVec3 color;
    UniformFloat density;
    UniformFloat gradient;

};

#endif
