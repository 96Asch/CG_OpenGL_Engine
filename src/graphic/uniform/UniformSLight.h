#ifndef UNIFORMSLIGHT_H_
#define UNIFORMSLIGHT_H_

#include "Uniform.h"
#include "UniformFloat.h"
#include "UniformPLight.h"
#include "../../component/SpotLight.h"

struct UniformSLight : public Uniform {

    UniformSLight(const std::string &name) : Uniform(name),
                                             point(UniformPLight(name + ".point")),
                                             direction(UniformVec3(name + ".direction")),
                                             cutoff(UniformFloat(name + ".cutoff"))
                                             {};

    virtual void storeUniformLocation(const GLuint &id) override {
        point.storeUniformLocation(id);
        direction.storeUniformLocation(id);
        cutoff.storeUniformLocation(id);
    }

    void load(const SpotLight &sLight,
              const glm::vec3 &pos,
              const glm::vec3 &dir)
    {
        point.load(sLight.point, pos);
        direction.load(dir);
        cutoff.load(sLight.cutoff);
    };


    UniformPLight point;
    UniformVec3 direction;
    UniformFloat cutoff;
};

#endif
