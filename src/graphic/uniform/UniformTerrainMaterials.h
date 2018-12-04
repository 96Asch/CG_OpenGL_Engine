#ifndef UNIFORMTERRAINMATERIALS_H_
#define UNIFORMTERRAINMATERIALS_H_

#include <memory>
#include <vector>

#include "UniformTerrainMaterial.h"
#include "Uniform.h"
#include "../../component/Material.h"

#define MAX_TERRAIN_MATERIALS 4

struct UniformTerrainMaterials : public Uniform {


    UniformTerrainMaterials(const std::string &name)
                    : Uniform(name)
    {
        tMaterials.resize(MAX_TERRAIN_MATERIALS);
        for(unsigned i = 0; i < MAX_TERRAIN_MATERIALS; ++i)
            tMaterials[i].reset(new UniformTerrainMaterial(name + "[" + std::to_string(i) + "]"));
    };

    virtual void storeUniformLocation(const GLuint &id) override {
        for(auto &mat : tMaterials)
            mat->storeUniformLocation(id);
    };

    void load(const std::vector<Material> &materials) {
        for(unsigned i  = 0; i < MAX_TERRAIN_MATERIALS; ++i) {
            if(i < materials.size())
                tMaterials[i]->load(materials[i]);
            else
                tMaterials[i]->load(Material(""));
        }
    };

    void load(const Material &material, const unsigned &index) {
        if(index < MAX_TERRAIN_MATERIALS)
            tMaterials[index]->load(material);
    };

    std::vector<std::unique_ptr<UniformTerrainMaterial>> tMaterials;
};

#endif
