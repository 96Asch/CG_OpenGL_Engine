#ifndef DESTRUCT_H_
#define DESTRUCT_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Destruct : public IComponent<Destruct> {

    Destruct(const float &time)
            : aliveTime(time)
              {};

    Destruct()
            : aliveTime(0.0f)
              {};

    Destruct(std::ifstream &stream)
               : aliveTime(0.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Destruct Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false);
        do {
            std::string buffer;
            std::string var;
            std::string value;
            stream >> std::ws;
            if(std::getline(stream, buffer)) {
                std::istringstream ss(buffer);
                if(!firstAcc && buffer == "{")
                    firstAcc = true;
                else if (firstAcc && buffer == "}")
                    lastAcc = true;
                else if(std::getline(ss, var, '=')) {
                    if (var == "aliveTime") {
                        if(std::getline(ss, value, '=')) {
                            this->aliveTime = std::stof(value);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    float aliveTime;
};

#endif
