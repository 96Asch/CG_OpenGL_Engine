#ifndef UNIFORMINTS_H_
#define UNIFORMINTS_H_

#include <memory>
#include <vector>
#include <initializer_list>

#include "Uniform.h"
#include "UniformInt.h"

struct UniformInts : public Uniform {

    UniformInts(const std::string &name, const size_t &size)
                    : Uniform(name),
                      size(size)
    {
        intArray.resize(size);
        for(unsigned i = 0; i < size; ++i)
            intArray[i].reset(new UniformInt(name + "[" + std::to_string(i) + "]"));
    };

    virtual void storeUniformLocation(const GLuint &id) override {
        for(auto &sampler : intArray)
            sampler->storeUniformLocation(id);
    };

    void load(std::initializer_list<int> &&ints) {
        unsigned count = 0;
        for(auto i : ints) {
            if(count < size)
                intArray[count]->load(i);
            ++count;
        }
    };

    const size_t size;
    std::vector<std::unique_ptr<UniformInt>> intArray;

};


#endif
