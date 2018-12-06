#ifndef UNIFORMTERRAINMATERIALS_H_
#define UNIFORMTERRAINMATERIALS_H_

#include <memory>
#include <vector>

#include "Uniform.h"
#include "UniformSpecular.h"

struct UniformSpeculars : public Uniform {


    UniformSpeculars(const std::string &name, const size_t &num)
                    : Uniform(name),
                      size(num)
    {
        specs.resize(num);
        for(unsigned i = 0; i < num; ++i)
            specs[i].reset(new UniformSpecular(name + "[" + std::to_string(i) + "]"));
    };

    virtual void storeUniformLocation(const GLuint &id) override {
        for(auto &s : specs)
            s->storeUniformLocation(id);
    };

    void load(const float &specularPower,
              const float &reflectance,
              const unsigned &index)
    {
        if(index < size)
            specs[index]->load(specularPower, reflectance);
    };

    size_t size;
    std::vector<std::unique_ptr<UniformSpecular>> specs;
};

#endif
