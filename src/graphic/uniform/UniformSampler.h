#ifndef UNIFORMSAMPLER_H_
#define UNIFORMSAMPLER_H_

#include "Uniform.h"

struct UniformSampler : public Uniform {

	UniformSampler(const std::string &name) : Uniform(name),
                                              first(true)
                                              {};

	void loadTexUnit(const unsigned &texUnit) {
		if (first || current != texUnit) {
			first = true;
			current = texUnit;
            glUniform1i(location, texUnit);
		}
	}

    unsigned current;
    bool first;

};

#endif
