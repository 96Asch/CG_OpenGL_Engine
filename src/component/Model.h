#ifndef MODEL_H_
#define MODEL_H_

#include <memory>
#include <sstream>
#include "Component.h"
#include "../graphic/globjects/Vao.h"
#include "../factory/VaoFactory.h"
#include "../factory/ModelLoader.h"

struct Model : public IComponent<Model> {

    Model(const std::string &source)
                   : source(source)
                   { Factory::loadOBJ(source); };

    Model(std::ifstream &stream) {
       if(!deserialize(stream))
            std::cerr << "ERR: Deserializing Model Component" << std::endl;
    };

    std::shared_ptr<Vao> getVao() {
       return Factory::VAO->getVao(source);
    };

    virtual bool deserialize(std::ifstream &stream) override {
        bool firstAcc(false), lastAcc(false);
        do {
            std::string buffer;
            std::string comp;
            std::string var;
            stream >> std::ws;
            if(std::getline(stream, buffer)) {
                std::istringstream ss(buffer);
                if(!firstAcc && buffer == "{")
                    firstAcc = true;
                else if (firstAcc && buffer == "}")
                    lastAcc = true;
                else if(std::getline(ss, comp, '=')) {
                    if (comp == "source")
                        if(std::getline(ss, var)) {
                            this->source = var;;
                            Factory::loadOBJ(source);
                        }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    std::string source;
};

#endif
