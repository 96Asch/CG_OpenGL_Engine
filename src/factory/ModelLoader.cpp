#include "ModelLoader.h"
#include "ObjLoader.h"
#include "VaoFactory.h"
#include "../graphic/globjects/Vao.h"

namespace Factory {
    namespace {
        objl::Loader loader;
        const float MIN_POSITION = -100.0f;
        const float MAX_POSITION = 100.0f;
    }

    void loadOBJ(const std::string &file) {
        bool success = false;
        glm::vec3 minEx, maxEx;
        if(VAO->isLoaded(file))
            return;

        success = loader.LoadFile((Global::resources + file).c_str());
        ModelData data;
        if(success) {
            std::cout << "Mesh num: " << loader.LoadedMeshes.size() << std::endl;
            objl::Mesh mesh = loader.LoadedMeshes.front();
            printf("Mesh: %s\n", mesh.MeshName.c_str());
            float minX(MAX_POSITION), minY(MAX_POSITION), minZ(MAX_POSITION),
                  maxX(MIN_POSITION), maxY(MIN_POSITION), maxZ(MIN_POSITION);
            for(unsigned i = 0; i < mesh.Vertices.size(); ++i) {
                float vx = mesh.Vertices[i].Position.X;
                float vy = mesh.Vertices[i].Position.Y;
                float vz = mesh.Vertices[i].Position.Z;

                minX = (vx < minX) ? vx : minX;
                minY = (vy < minY) ? vy : minY;
                minZ = (vz < minZ) ? vz : minZ;

                maxX = (vx > maxX) ? vx : maxX;
                maxY = (vy > maxY) ? vy : maxY;
                maxZ = (vz > maxZ) ? vz : maxZ;

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
            minEx = glm::vec3(minX, minY, minZ);
            maxEx = glm::vec3(maxX, maxY, maxZ);
        }
        else {
            std::cerr << "Loading object has failed!" << std::endl;
        }
        VAO->createVao(file,
                       data.indices,
                       data.vertices,
                       data.textures,
                       data.normals,
                       minEx,
                       maxEx);
    }

}
