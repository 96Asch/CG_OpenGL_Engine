#ifndef FLATMESH_H_
#define FLATMESH_H_

#include "Mesh.h"

struct FlatMesh : Mesh {

    int vertexCount = 4;
    int QUAD_INDICES[6] = { 0, 1, 3, 3, 1, 2 };
    float QUAD_POSITIONS[8] = { -1, -1, -1, 1, 1, 1, 1, -1 };
};

#endif
