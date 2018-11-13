#include "ModelLoader.h"
#include "ObjLoader.h"
#include "VaoFactory.h"
#include "../graphic/globjects/Vao.h"

namespace Factory {
    namespace {
        objl::Loader loader;
    }

    Vao* loadOBJ(const std::string &file) {
        bool success = false;

        success = loader.LoadFile((Global::resources + file).c_str());
        ModelData data;
        if(success) {
            std::cout << "Mesh num: " << loader.LoadedMeshes.size() << std::endl;
            objl::Mesh mesh = loader.LoadedMeshes.front();
            printf("Mesh: %s\n", mesh.MeshName.c_str());

            for(unsigned i = 0; i < mesh.Vertices.size(); ++i) {
                data.vertices.push_back(mesh.Vertices[i].Position.X);
                data.vertices.push_back(mesh.Vertices[i].Position.Y);
                data.vertices.push_back(mesh.Vertices[i].Position.Z);

                data.textures.push_back(mesh.Vertices[i].TextureCoordinate.X);
                data.textures.push_back(mesh.Vertices[i].TextureCoordinate.Y);

                data.normals.push_back(mesh.Vertices[i].Normal.X);
                data.normals.push_back(mesh.Vertices[i].Normal.Y);
                data.normals.push_back(mesh.Vertices[i].Normal.Z);
            }

            data.indices = mesh.Indices;
        }
        else {
            std::cerr << "Loading object has failed!" << std::endl;
            return nullptr;
        }

        return VAO->createVao(data.vertices, data.indices, data.textures, data.normals);

    }
}
