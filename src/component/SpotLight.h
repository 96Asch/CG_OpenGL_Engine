#ifndef SPOTLIGHT_H_
#define SPOTLIGHT_H_

struct SpotLight : public IComponent<SpotLight> {

    SpotLight() {};

    SpotLight(std::ifstream &stream) : cutoff(0.5f)
    {
        if(!deserialize(stream))
             std::cerr << "ERR: Deserializing PointLight Component" << std::endl;
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false), ret(true);
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
                    if (var == "[pointlight]") {
                        ret &= point.deserialize(stream);
                    }
                    else if (var == "cutoff") {
                        if(std::getline(ss, value, '=')) {
                            this->cutoff = std::stof(value);
                        }
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true & ret;
    };

    virtual void serialize(std::ofstream &) override {};

    PointLight point;
    float cutoff;

};

#endif
