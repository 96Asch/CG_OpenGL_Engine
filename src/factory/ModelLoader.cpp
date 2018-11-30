#include "ModelLoader.h"
#include "ObjLoader.h"
#include "VaoFactory.h"
#include "../graphic/globjects/Vao.h"

namespace Factory {
    namespace {
        objl::Loader loader;
    }

    void loadOBJ(const std::string &file, const float &scale) {
        bool success = false;
        if(VAO->isLoaded(file))
            return;

        success = loader.LoadFile((Global::resources + file).c_str());
        ModelData data;
        if(success) {
            std::cout << "Mesh num: " << loader.LoadedMeshes.size() << std::endl;
            objl::Mesh mesh = loader.LoadedMeshes.front();
            printf("Mesh: %s\n", mesh.MeshName.c_str());

            for(unsigned i = 0; i < mesh.Vertices.size(); ++i) {
                std::cout << mesh.Vertices[i].Position.X * scale << std::endl;
                data.vertices.push_back(mesh.Vertices[i].Position.X * scale);
                data.vertices.push_back(mesh.Vertices[i].Position.Y * scale);
                data.vertices.push_back(mesh.Vertices[i].Position.Z * scale);

                data.textures.push_back(mesh.Vertices[i].TextureCoordinate.X * scale);
                data.textures.push_back(mesh.Vertices[i].TextureCoordinate.Y * scale);

                data.normals.push_back(mesh.Vertices[i].Normal.X * scale);
                data.normals.push_back(mesh.Vertices[i].Normal.Y * scale);
                data.normals.push_back(mesh.Vertices[i].Normal.Z* scale);
            }

            data.indices = mesh.Indices;
        }
        else {
            std::cerr << "Loading object has failed!" << std::endl;
        }
        VAO->createVao(file, data.vertices, data.indices, data.textures, data.normals);
    }

}
