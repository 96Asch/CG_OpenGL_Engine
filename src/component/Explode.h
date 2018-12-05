#ifndef EXPLODE_H_
#define EXPLODE_H_

#include "Component.h"
#include <sstream>
#include <glm/vec3.hpp>

struct Explode : public IComponent<Explode> {

    Explode(const bool &active, const float &speed, const float &maxDistance)
            : active(active),
              speed(speed),
              distance(0.0f),
              lastDistance(0.0f),
              interpolated(0.0f),
              maxDistance(maxDistance)
              {};
    Explode()
            : active(0),
              speed(0.0f),
              distance(0.0f),
              lastDistance(0.0f),
              interpolated(0.0f),
              maxDistance(0.0f)
              {};

    Explode(std::ifstream &stream)
               : active(0),
                 speed(0.0f),
                 distance(0.0f),
                 lastDistance(0.0f),
                 interpolated(0.0f),
                 maxDistance(0.0f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing Explode Component" << std::endl;
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
                    if (var == "speed") {
                        if(std::getline(ss, value, '=')) {
                            this->speed = std::stof(value);
                        }
                    }
                    else if (var == "active") {
                        if(std::getline(ss, value, '=')) {
                            this->active = std::stoi(value);
                        }
                    }
                    else if (var == "maxDistance") {
                        if(std::getline(ss, value, '=')) {
                            this->maxDistance = std::stof(value);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    bool active;
    float speed;
    float distance, lastDistance, interpolated;
    float maxDistance;
};

#endif
