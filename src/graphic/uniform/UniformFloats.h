#ifndef UNIFORMFLOATS_H_
#define UNIFORMFLOATS_H_

#include <memory>
#include <vector>
#include <initializer_list>

#include "Uniform.h"
#include "UniformFloat.h"

struct UniformFloats : public Uniform {

    UniformFloats(const std::string &name, const size_t &size)
                    : Uniform(name),
                      size(size)
    {
        floatArray.resize(size);
        for(unsigned i = 0; i < size; ++i)
            floatArray[i].reset(new UniformFloat(name + "[" + std::to_string(i) + "]"));
    };

    virtual void storeUniformLocation(const GLuint &id) override {
        for(auto &sampler : floatArray)
            sampler->storeUniformLocation(id);
    };

    void load(std::initializer_list<float> &&floats) {
        unsigned count = 0;
        for(auto i : floats) {
            if(count < size)
                floatArray[count]->load(i);
            ++count;
        }
    };

    void load(const float &val, const unsigned &index) {
        if(index < size)
            floatArray[index]->load(val);
    };

    const size_t size;
    std::vector<std::unique_ptr<UniformFloat>> floatArray;

};


#endif
