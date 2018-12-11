#ifndef MODEL_H_
#define MODEL_H_

#include <memory>
#include <sstream>
#include "Component.h"
#include "../graphic/globjects/Vao.h"
#include "../factory/VaoFactory.h"
#include "../factory/Texture.h"
#include "../factory/TextureFactory.h"
#include "../factory/ModelLoader.h"

struct Model : public IComponent<Model> {

    Model(const std::string &mesh,
          const Texture &texture)
                   : mesh(mesh),
                     texture(texture)
    {
        Factory::loadOBJ(mesh);
        this->texture.loadCurrent();
    };

    Model(std::ifstream &stream) {
       if(!deserialize(stream))
            std::cerr << "ERR: Deserializing Model Component" << std::endl;
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
                    if (var == "mesh") {
                        if(std::getline(ss, value)) {
                            this->mesh = value;
                            Factory::loadOBJ(mesh);
                        }
                    }
                    else if (var == "[texture]") {
                        texture.deserialize(stream);
                    }
                }
            }
            else return false;
        } while(stream && firstAcc && !lastAcc);
        return true;
    };

    virtual void serialize(std::ofstream &) override {};

    std::shared_ptr<Vao> getVao() {
        return Factory::VAO->getVao(mesh);
    };

    std::string mesh;
    Texture texture;

};

#endif
