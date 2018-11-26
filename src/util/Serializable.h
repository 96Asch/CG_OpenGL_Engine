#ifndef SERIALIZABLE_H_
#define SERIALIZABLE_H_

#include <iostream>
#include <fstream>

class Serializable {

public:

    virtual ~Serializable() {};

    virtual void serialize(std::ofstream &out) = 0;

    virtual bool deserialize(std::ifstream &stream) = 0;

};


#endif
